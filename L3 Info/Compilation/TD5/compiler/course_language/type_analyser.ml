open Ast

let type_of_binop op expr_type =
  match op with
  | Add | Sub | Mul | Div | Mod ->
      if expr_type = Basic TInt then TInt
      else if expr_type = Basic TFloat then TFloat
      else TNull
  | And | Or -> if expr_type = Basic TBool then TBool else TNull
  | Eq | Neq | Leq | Geq | Lt | Gt -> TBool

let type_of_unop op expr_type =
  match op with
  | UMin ->
      if expr_type = Basic TInt then TInt
      else if expr_type = Basic TFloat then TFloat
      else TNull
  | Not -> TBool

let rec type_expr type_env init_env func_env report expr =
  ignore (type_of_binop, type_of_unop);
  ignore (type_expr, type_env, init_env, func_env);
  let pos = Annotation.get_pos (expr_get_annotation expr) in
  match expr with
  | _ ->
      Util.Error_report.add_error report
        (Format.sprintf "I haven't typed anything : error %d" 1, pos);
      Basic TNull

let rec type_instruction type_env init_env func_env report instruction =
  ignore (type_instruction, type_env, init_env, func_env);
  let pos = Annotation.get_pos (instruction_get_annotation instruction) in
  match instruction with
  | _ ->
      Util.Error_report.add_warning report
        (Format.sprintf "Untyped instruction : error %s" "toto", pos)

let type_arg report pos argument =
  match argument with
  | _ ->
      Util.Error_report.add_error report ("Argument not typed", pos);
      (Value, Basic TNull)

let type_func_decl func_env report = function
  | Func_decl (typ, name, args, body, annotation) ->
      ignore (func_env, typ, args, body);
      let pos = Annotation.get_pos annotation in
      Util.Error_report.add_error report
        (Format.sprintf "%s was not typed" name, pos)
