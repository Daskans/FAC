module Environment = struct
  type value =
    | VInt of int
    | VBool of bool
    | VFloat of float
    | VPointer of Ast.address * t

  and t = {
    memory : (Ast.address, value ref) Hashtbl.t;
    global_memory : (int, value ref) Hashtbl.t;
    mutable next_free_block : int;
    mutable param : Ast.address list;
    mutable program_pointer : int;
    label_map : (Ast.label, int) Hashtbl.t;
    program : (int, Ast.instruction) Hashtbl.t;
  }

  let create_empty prg =
    let res =
      {
        memory = Hashtbl.create 10;
        global_memory = Hashtbl.create 10;
        next_free_block = 0;
        param = [];
        program_pointer = 0;
        label_map = Hashtbl.create 10;
        program = Hashtbl.create (List.length prg) (*to modify*);
      }
    in
    Hashtbl.replace res.memory (Ast.address_of_string "#result#") (ref (VInt 0));
    List.iteri
      (fun pos (lbl, instr) ->
        Hashtbl.replace res.program pos instr;
        if lbl <> Ast.label_of_string "" then
          Hashtbl.replace res.label_map lbl pos)
      prg;
    res

  let set_var env label value =
    match Hashtbl.find_opt env.memory label with
    | Some r -> r := value
    | None -> Hashtbl.replace env.memory label (ref value)

  let get_var env label = !(Hashtbl.find env.memory label)
  let push_param env param = env.param <- param :: env.param

  let pop_param env =
    let r = List.hd env.param in
    env.param <- List.tl env.param;
    r

  let get_tab_value env tab position =
    match (get_var env tab, position) with
    | VInt a, VInt b -> !(Hashtbl.find env.global_memory (a + b))
    | _ -> failwith "segfault get"

  let set_tab_value env tab position value =
    match (get_var env tab, position) with
    | VInt a, VInt b -> (
        match Hashtbl.find_opt env.global_memory (a + b) with
        | Some r -> r := value
        | None -> Hashtbl.replace env.global_memory (a + b) (ref value))
    | _ -> failwith "segfault set"

  let prepare_env_call env n =
    let res = { env with memory = Hashtbl.create 10; param = [] } in
    for i = 0 to n - 1 do
      let p = pop_param env in
      let arg = Ast.address_of_parameter i in
      Hashtbl.replace res.memory arg (Hashtbl.find env.memory p)
      (*try
          Hashtbl.replace res.memory
            (Ast.get_address_size_tab arg)
            (Hashtbl.find env.memory (Ast.get_address_size_tab p))
        with _ -> ()*)
    done;
    Hashtbl.replace res.memory
      (Ast.address_of_string "#result#")
      (Hashtbl.find env.memory (Ast.address_of_string "#result#"));
    res

  let next_instruction env = env.program_pointer <- env.program_pointer + 1

  let goto_label env label =
    env.program_pointer <- Hashtbl.find env.label_map label

  let get_instruction env = Hashtbl.find env.program env.program_pointer

  let get_next_free_block env size =
    let r = env.next_free_block in
    env.next_free_block <- env.next_free_block + size;
    r
end

type value = Environment.value

open Ast

let get_val env = function
  | Name add -> Environment.get_var env add
  | Int i -> VInt i
  | Float f -> VFloat f
  | Bool b -> VBool b

let op_of_binop b (v1 : value) (v2 : value) : value =
  match (b, v1, v2) with
  | Add_i, VInt a, VInt b -> VInt (a + b)
  | Sub_i, VInt a, VInt b -> VInt (a - b)
  | Mul_i, VInt a, VInt b -> VInt (a * b)
  | Div_i, VInt a, VInt b -> VInt (a / b)
  | Mod_i, VInt a, VInt b -> VInt (a mod b)
  | Add_f, VFloat a, VFloat b -> VFloat (a +. b)
  | Sub_f, VFloat a, VFloat b -> VFloat (a -. b)
  | Mul_f, VFloat a, VFloat b -> VFloat (a *. b)
  | Div_f, VFloat a, VFloat b -> VFloat (a /. b)
  | Mod_f, VFloat a, VFloat b -> VFloat (mod_float a b)
  | And, VBool a, VBool b -> VBool (a && b)
  | Or, VBool a, VBool b -> VBool (a || b)
  | Eq, a, b -> VBool (a = b)
  | Neq, a, b -> VBool (a <> b)
  | Lt, VInt a, VInt b -> VBool (a < b)
  | Lt, VFloat a, VFloat b -> VBool (a < b)
  | Lt, VBool a, VBool b -> VBool (a < b)
  | Gt, VInt a, VInt b -> VBool (a > b)
  | Gt, VFloat a, VFloat b -> VBool (a > b)
  | Gt, VBool a, VBool b -> VBool (a > b)
  | Leq, VInt a, VInt b -> VBool (a <= b)
  | Leq, VFloat a, VFloat b -> VBool (a <= b)
  | Leq, VBool a, VBool b -> VBool (a <= b)
  | Geq, VInt a, VInt b -> VBool (a >= b)
  | Geq, VFloat a, VFloat b -> VBool (a >= b)
  | Geq, VBool a, VBool b -> VBool (a >= b)
  | _ -> failwith "wrong operand"

let op_of_unop u (v : value) : value =
  match (u, v) with
  | UMin, VInt a -> VInt (-a)
  | UMin_f, VFloat a -> VFloat (-.a)
  | Not, VBool b -> VBool (not b)
  | _ -> failwith "wrong operand"

let rec interpret_loop env =
  match Environment.get_instruction env with
  | Binop (address, binop, val1, val2) ->
      let v1 = get_val env val1 in
      let v2 = get_val env val2 in
      Environment.set_var env address (op_of_binop binop v1 v2);
      Environment.next_instruction env;
      interpret_loop env
  | Unop (address, unop, value) ->
      let v = get_val env value in
      Environment.set_var env address (op_of_unop unop v);
      Environment.next_instruction env;
      interpret_loop env
  | Copy (address, value) ->
      Environment.set_var env address (get_val env value);
      Environment.next_instruction env;
      interpret_loop env
  | ADecl (tab, size) -> (
      let s = get_val env size in
      match s with
      | VInt a ->
          let base = Environment.get_next_free_block env (a + 1) in
          Environment.set_var env tab (VInt (base + 1));
          Environment.set_tab_value env tab (VInt (-1)) s;
          Environment.next_instruction env;
          interpret_loop env
      | _ -> failwith "declaring an array of non-integer size")
  | ACopy ((tab, pos), value) ->
      Environment.set_tab_value env tab (get_val env pos) (get_val env value);
      Environment.next_instruction env;
      interpret_loop env
  | ALoad (address, (tab, pos)) ->
      Environment.set_var env address
        (Environment.get_tab_value env tab (get_val env pos));
      Environment.next_instruction env;
      interpret_loop env
  | AddressOf (tgt, src) ->
      Environment.set_var env tgt (VPointer (src, env));
      Environment.next_instruction env;
      interpret_loop env
  | SetPointed (tgt, src) ->
      (match Environment.get_var env tgt with
      | VPointer (address, point_env) ->
          Environment.set_var point_env address (get_val env src)
      | _ -> failwith "Dereferencing a non-pointer value");
      Environment.next_instruction env;
      interpret_loop env
  | GetPointed (tgt, src) ->
      (match Environment.get_var env src with
      | VPointer (address, point_env) ->
          Environment.set_var env tgt (Environment.get_var point_env address)
      | _ -> failwith "Dereferencing a non-pointer value");
      Environment.next_instruction env;
      interpret_loop env
  | Goto label ->
      Environment.goto_label env label;
      interpret_loop env
  | IfTrue (value, label) ->
      (match get_val env value with
      | VBool true -> Environment.goto_label env label
      | _ -> Environment.next_instruction env);
      interpret_loop env
  | IfFalse (value, label) ->
      (match get_val env value with
      | VBool false -> Environment.goto_label env label
      | _ -> Environment.next_instruction env);
      interpret_loop env
  | Param address ->
      Environment.push_param env address;
      Environment.next_instruction env;
      interpret_loop env
  | Call (label, num_args) ->
      let new_env = Environment.prepare_env_call env num_args in
      Environment.goto_label new_env label;
      interpret_loop new_env;
      Environment.next_instruction env;
      interpret_loop env
  | Noop ->
      ();
      Environment.next_instruction env;
      interpret_loop env
  | Return -> ()
  | Print_int value ->
      (match get_val env value with
      | VInt a -> print_int a
      | _ -> failwith "type_error");
      Environment.next_instruction env;
      interpret_loop env
  | Print_float value ->
      (match get_val env value with
      | VFloat a -> print_float a
      | _ -> failwith "type_error");
      Environment.next_instruction env;
      interpret_loop env
  | Print_bool value ->
      (match get_val env value with
      | VBool a -> if a then print_string "true" else print_string "false"
      | _ -> failwith "type_error");
      Environment.next_instruction env;
      interpret_loop env
  | Print str ->
      print_string str;
      Environment.next_instruction env;
      interpret_loop env

let execute_prg prg =
  if prg = [] then Format.printf "Empty program\n"
  else
    let env = Environment.create_empty prg in
    interpret_loop env
