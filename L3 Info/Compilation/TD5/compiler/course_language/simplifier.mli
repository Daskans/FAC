(** Module that allow to simplify constant expressions and dead code in an annotated Ast.*)

val simplify_expr : Ast.expr -> Ast.expr
(** [simplify_expr expr] simplifies [expr] and returns the result.
    It simply replaces constant terms by their result.*)

val simplify_instruction : Ast.instruction -> Ast.instruction
(** [simplify_instruction instruction] simplifies [instr] and returns the result. It simplifies the inner expressions, simplifies ifthenelse statement whose test is constant and removes while loop that can never be taken.*)

val simplify_func_decl : Ast.function_decl -> Ast.function_decl
(** [simplify_func_decl f] simplifies the body of [f].*)
