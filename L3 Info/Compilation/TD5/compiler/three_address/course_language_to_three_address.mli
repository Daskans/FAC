(** Module to converts an {!Course_language.Ast} to a {!Ast.labelled_instruction} list*)

module Counter : sig
  (** Module to get fresh addresses and labels when generating the code. Must only use one for a full Course_language.Ast.*)

  type t
  (**The counter*)

  val create : unit -> t
  (**Creates an initialised counter*)

  val get_fresh_address : t -> Ast.address
  (**Returns a fresh address.*)

  val get_fresh_label : t -> Ast.label
  (**Returns a freh label.*)
end

module Arg_mapper : sig
  (** Module to replace variable that are parameters in function declaration by their parameter identifiers. One must be used for each function declaration.*)

  type t
  (** The mapper of variable names to their parameter names.*)

  val create : unit -> t
  (** Creates an empty mapper.*)

  val add_binding : t -> string -> Course_language.Ast.type_argument -> unit
  (** [add_binging mapper name typ] sets the variable [name] to be an argument of the program, associating it a unique technical name, and storing its parameter type. Used to set parameters in the declaration of function parameters.*)

  val is_parameter : t -> string -> bool
  (** [is_parametr mapper name] is true if [name] is a parameter in the current function.*)

  val get_address : t -> string -> Ast.address
  (** Gets the true name of a variable. If that variable is a parameter, it returns its parameter name, otherwise leaves it unchanged.*)

  val get_param_type : t -> string -> Course_language.Ast.type_argument
  (** Gets the parameter type associated to a variable, if it is a parameter of the current function. Fails if it is not.*)
end

val expr_to_code :
  Counter.t ->
  Arg_mapper.t ->
  Course_language.Ast.expr ->
  Ast.r_value * (Ast.label * Ast.instruction) list
(** Converts an annotated expression to three address code. [expr_to_code counter mapper code expr] converts [expr] to three address code and appends it to [code]. It does it by using [counter] to get fresh addresses when needed and [mapper] to get true argument names of variables.*)

val instruction_to_code :
  Counter.t ->
  Arg_mapper.t ->
  Course_language.Ast.instruction ->
  (Ast.label * Ast.instruction) list
(** Converts an annotated instruction to three address code. Works as [expr_to_code].*)

val function_decl_to_code :
  Counter.t ->
  Course_language.Ast.function_decl ->
  (Ast.label * Ast.instruction) list
(** Converts an annotated function declaration to three address code. Needs to create an {!Arg_mapper.t} to converts its body.*)

val program_to_code :
  Course_language.Ast.function_decl list -> (Ast.label * Ast.instruction) list
(** Converts a full program to three address code. Needs to initialise a {!Counter.t}.*)
