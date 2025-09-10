(** Modules that annotates an Ast with types of expressions and arguments, and report errors.*)

val type_expr :
  Ast.type_value Util.Environment.t ->
  bool Util.Environment.t ->
  (Ast.type_basic * (Ast.type_argument * Ast.type_value) list)
  Util.Environment.t ->
  Util.Error_report.t ->
  Ast.expr ->
  Ast.type_value
(** [type_expr type_env init_env func_env report expr] annotates [expr] with its type, reports eventual errors and warnings in [report], and annotates function calls arguments with their types. It also returns the type which annotates [expr] (for use in recursive calls).
    [type_env] is an environment linking declared variables to their types.
    [init_env] is an environment linking declared variables to true if they were already initialized, and false otherwise.
    [func_env] is an environment linking declared function names to their function types.*)

val type_instruction :
  Ast.type_value Util.Environment.t ->
  bool Util.Environment.t ->
  (Ast.type_basic * (Ast.type_argument * Ast.type_value) list)
  Util.Environment.t ->
  Util.Error_report.t ->
  Ast.instruction ->
  unit
(** [type_instruction type_env init_env func_env report instr] types all expressions appearing in [instr].
    [type_env] is an environment linking declared variables to their types.
    [init_env] is an environment linking declared variables to true if they were already initialized, and false otherwise.
    [func_env] is an environment linking declared function names to their function types.*)

val type_arg :
  Util.Error_report.t ->
  Util.Position.t ->
  Ast.argument ->
  Ast.type_argument * Ast.type_value
(** [type_arg report pos arg] determines the type of [arg], and returns it.*)

val type_func_decl :
  (Ast.type_basic * (Ast.type_argument * Ast.type_value) list)
  Util.Environment.t ->
  Util.Error_report.t ->
  Ast.function_decl ->
  unit
(** [type_func_decl func_env report f] types function [f] and its body.
    [func_env] is an environment linking declared function names to their function types.*)
