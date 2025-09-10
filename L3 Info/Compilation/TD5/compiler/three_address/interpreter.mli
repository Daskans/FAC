(** Interpreter of Three address code. Displays its output in stdout.*)

val execute_prg : (Ast.label * Ast.instruction) list -> unit
