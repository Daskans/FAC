open Ast

let rec simplify_expr expr =
  ignore simplify_expr;
  expr
(*to modify*)
(*match expr with
  | Unop (op, e,annotation) -> expr
  | Binop (op, e1, e2,annotation) -> expr
  | Array_val (tab, e,annotation) -> expr
  | Func (name, args,annotation) -> expr
  | Cst_i (i,annotation) -> expr
  | Cst_f (f,annotation) -> expr
  | Cst_b (b,annotation) -> expr
  | Var (s,annotation) -> expr
  | Size_tab (s,annotation) -> expr*)

let rec simplify_instruction instruction =
  ignore simplify_instruction;
  instruction
(*to modify*)
(*match instruction with
  | Affect (name, expr,annotation) -> instruction
  | Block (l,annotation) -> instruction
  | IfThenElse (test, i_then, i_else,annotation) -> instruction
  | While (test, body,annotation) -> instruction
  | Affect_array (name, pos, value,annotation) -> instruction
  | Array_decl (typ, name, size,annotation) -> instruction
  | Proc (name, args,annotation) -> instruction
  | Return (o,annotation) -> instruction
  | Print_str (s,annotation) -> instruction
  | Print_expr (expr,annotation) -> instruction
  | Var_decl (typ, name,annotation) -> instruction*)

let simplify_func_decl = function
  | Func_decl (typ, name, args, body, annotation) ->
      Func_decl (typ, name, args, simplify_instruction body, annotation)
