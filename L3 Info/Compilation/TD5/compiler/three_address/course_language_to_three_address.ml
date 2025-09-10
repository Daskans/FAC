open Course_language.Ast
open Ast

module Counter = struct
  type t = { mutable next_address : int; mutable next_label : int }

  let create () = { next_address = 0; next_label = 0 }

  let get_fresh_address counter =
    let add = address_of_string (Format.sprintf "#%d" counter.next_address) in
    counter.next_address <- counter.next_address + 1;
    add

  let get_fresh_label counter =
    let lbl = label_of_string (Format.sprintf "_Lbl%d" counter.next_label) in
    counter.next_label <- counter.next_label + 1;
    lbl
end

module Arg_mapper = struct
  type t = {
    mapping : (string, Ast.address * type_argument) Hashtbl.t;
    mutable num_args : int;
  }

  let create () = { mapping = Hashtbl.create 10; num_args = 0 }

  let add_binding mapper name param_type =
    Hashtbl.replace mapper.mapping name
      (Ast.address_of_parameter mapper.num_args, param_type);
    mapper.num_args <- mapper.num_args + 1

  let is_parameter mapper name = Hashtbl.mem mapper.mapping name

  let get_address mapper name =
    match Hashtbl.find_opt mapper.mapping name with
    | None -> Ast.address_of_string name
    | Some (a, _) -> a

  let get_param_type mapper name =
    match Hashtbl.find_opt mapper.mapping name with
    | None -> failwith "getting parameter type of a non parameter variable"
    | Some (_, p_type) -> p_type
end

let binop_of_binop typ = function
  | Add -> if typ = Basic TInt then Add_i else Add_f
  | Sub -> if typ = Basic TInt then Sub_i else Sub_f
  | Mul -> if typ = Basic TInt then Mul_i else Mul_f
  | Div -> if typ = Basic TInt then Div_i else Div_f
  | Mod -> if typ = Basic TInt then Mod_i else Mod_f
  | And -> And
  | Or -> Or
  | Eq -> Eq
  | Neq -> Neq
  | Lt -> Lt
  | Gt -> Gt
  | Leq -> Leq
  | Geq -> Geq

let unop_of_unop typ = function
  | Course_language.Ast.UMin -> if typ = Basic TInt then UMin else UMin_f
  | Not -> Not

let rec expr_to_code counter mapper expr =
  (*todo*)
  ignore (binop_of_binop, unop_of_unop);
  ignore (counter, mapper, expr, expr_to_code);
  (Int 0, [ (no_label, Noop) ])

let rec instruction_to_code counter mapper instruction =
  (*todo*)
  ignore (counter, mapper, instruction, instruction_to_code);
  [ (no_label, Noop) ]

let function_decl_to_code counter func_decl =
  match func_decl with
  | Func_decl (_, name, _, _, _) ->
      (*todo*)
      ignore (counter, func_decl);
      [ (label_of_string name, Noop) ]

let program_to_code prg =
  let counter = Counter.create () in
  let code =
    List.fold_left
      (fun code func -> code @ function_decl_to_code counter func)
      [] prg
  in
  code
