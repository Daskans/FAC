open Ast
open Abstract_machine

exception Return_exp of value option
exception Non_variable_reference of expr
exception Non_bool_test of expr
exception Non_integer_array_position of expr

let get_tab_pos name pos = name ^ string_of_int pos

let operation_of_binop op v1 v2 =
  match op with
  | Add -> ( match v1 with VFloat _ -> add_f v1 v2 | _ -> add_i v1 v2)
  | Sub -> ( match v1 with VFloat _ -> sub_f v1 v2 | _ -> sub_i v1 v2)
  | Mul -> ( match v1 with VFloat _ -> mul_f v1 v2 | _ -> mul_i v1 v2)
  | Div -> ( match v1 with VFloat _ -> div_f v1 v2 | _ -> div_i v1 v2)
  | Mod -> ( match v1 with VFloat _ -> mod_f v1 v2 | _ -> mod_i v1 v2)
  | And -> and_b v1 v2
  | Or -> or_b v1 v2
  | Eq -> eq_m v1 v2
  | Neq -> not_b (eq_m v1 v2)
  | Lt -> lt_m v1 v2
  | Gt -> lt_m v2 v1
  | Leq -> or_b (lt_m v1 v2) (eq_m v1 v2)
  | Geq -> or_b (lt_m v2 v1) (eq_m v1 v2)

let operation_of_unop op v =
  match (op, v) with
  | UMin, VFloat f -> sub_f (VFloat 0.) (VFloat f)
  | UMin, _ -> sub_i (VInt 0) v
  | Not, _ -> not_b v

let rec interpret_expr env env_function = function
  | Cst_i (i, _) -> VInt i
  | Cst_f (f, _) -> VFloat f
  | Cst_b (b, _) -> VBool b
  | Var (s, _) -> (
      match Util.Environment.get env s with
      | Some m -> m
      | None -> raise Not_found)
  | Binop (op, e1, e2, _) ->
      let v1 = interpret_expr env env_function e1 in
      let v2 = interpret_expr env env_function e2 in
      (operation_of_binop op) v1 v2
  | Unop (op, e, _) ->
      let v = interpret_expr env env_function e in
      (operation_of_unop op) v
  | Array_val (name, pos, _) -> (
      let v_pos =
        (match (interpret_expr env env_function pos) with
        | VInt p -> p
        | _ -> raise (Non_integer_array_position pos)) in
      let (name, env)=
        (match Util.Environment.get env name with
        | Some (VArray (name, env)) -> (name, env)
        | _ -> raise Not_found)
      in
      try
        match Util.Environment.get env (get_tab_pos name v_pos) with
        | Some a -> a
        | None -> VNone
      with _ -> VNone)
  | Size_tab (name, _) ->
      let (name, env)=(
      match Util.Environment.get env name with
      | Some (VArray (name, env)) -> (name, env)
      | _ -> raise Not_found)
      in
        Option.get (Util.Environment.get env (name ^ "size"))
  | Func (name, args, _) -> (
      let new_env = Util.Environment.new_environment () in
      let decl_list, body =
        Option.get (Util.Environment.get env_function name) in
      let aux expr decl =(
        match decl with
        | Value, Basic _, name ->
            Util.Environment.modify new_env name
              (interpret_expr env env_function expr)
        | Value, Array_t _, name | Reference, _, name -> (
            match expr with
            | Var (var, _) -> (
                match Util.Environment.get_ref env var with
                | Some cell -> Util.Environment.add_ref new_env name cell
                | None -> raise Not_found)
            | Array_val (tab, pos, _) -> (
                let v_pos = (
                  match interpret_expr env env_function pos with 
                  | VInt a -> a
                  | _ -> raise Not_found) in
                let (name, env)=(
                  match Util.Environment.get env tab with
                  | Some (VArray (name, env)) -> (name, env)
                  | _ -> raise Not_found) in
                let r = Option.get (Util.Environment.get_ref env (name^ string_of_int v_pos))
                in
                Util.Environment.add_ref new_env name r)
            | _ -> raise (Non_variable_reference expr)))
      in
      List.iter2 aux (List.rev args) (List.rev decl_list);
      try
        interpret_instruction new_env env_function body;
        VNone
      with
      | Return_exp (Some v) -> v
      | Return_exp None -> VNone
      | a -> raise a)

and interpret_instruction env env_function instruction =
  match instruction with
  | Affect (var, e, _) ->
      let v = interpret_expr env env_function e in
      Util.Environment.modify env var v
  | Block (l, _) -> List.iter (interpret_instruction env env_function) l
  | IfThenElse (test, th, el, _) -> (
      match interpret_expr env env_function test with
      | VBool true -> interpret_instruction env env_function th
      | VBool false -> interpret_instruction env env_function el
      | _ -> raise (Non_bool_test test))
  | While (test, loop, _) -> (
      match interpret_expr env env_function test with
      | VBool true ->
          interpret_instruction env env_function loop;
          interpret_instruction env env_function instruction
      | VBool false -> ()
      | _ -> raise (Non_bool_test test))
  | Affect_array (name, pos, e, _) -> (
      let v_pos =
        match (interpret_expr env env_function pos) with
        | VInt a -> a
        | _ -> raise (Non_integer_array_position pos) in
      let v = interpret_expr env env_function e in
      match Util.Environment.get env name with
      | Some (VArray (tab_name, tab_env)) ->
          Util.Environment.modify tab_env (get_tab_pos tab_name v_pos) v
      | _ -> raise Not_found)
  | Var_decl (_, _, _) -> ()
  | Array_decl (_, name, size, _) ->
      let v_size = interpret_expr env env_function size in
      Util.Environment.modify env name (VArray (name ^ "#", env));
      Util.Environment.modify env (name ^ "#size") v_size
  | Print_str (str, _) -> Format.printf "%s" str
  | Print_expr (expr, _) ->
      Format.printf "%s"
        (string_of_value (interpret_expr env env_function expr))
  | Return (Some expr, _) ->
      let v = interpret_expr env env_function expr in
      raise (Return_exp (Some v))
  | Return (None, _) -> raise (Return_exp None)
  | Proc (name, args, annot) ->
      ignore (interpret_expr env env_function (Func (name, args, annot)))

let interpret_func_decl functions = function
  | Func_decl (_, name, args, body, _) ->
      Util.Environment.modify functions name (args, body)

let normalize_arg_list args vars =
  if List.length args < List.length vars then
    args @ List.init (List.length vars - List.length args) (fun _ -> "")
  else if List.length args > List.length vars then
    List.filteri (fun i _ -> i < List.length vars) args
  else args

let interpret_prg prg args =
  let functions = Util.Environment.new_environment () in
  List.iter (interpret_func_decl functions) prg;
  let environnement = Util.Environment.new_environment () in
  let params, body =
    try Option.get (Util.Environment.get functions "main")
    with _ -> failwith "Function main not defined!"
  in
  let vars = List.map (fun (_, _, v) -> v) params in
  let args = normalize_arg_list args vars in
  List.iter2
    (fun v a ->
      Abstract_machine.parse_complex_argument_and_affect environnement v a)
    vars args;
  try interpret_instruction environnement functions body
  with Return_exp _ -> ()
