(** Module representing the Three Adress Code of the backend of the compiler.*)

type label
(** Type for labels of the code*)

val label_of_string : string -> label
(** Creates a label of name given in argument*)

val string_of_label : label -> string
(** Gets the label associated with the label given in argument*)

val no_label : label
(** Empty label*)

(** Type for addresses of the code.*)
type address = Local of string | Parameter of int

val address_of_string : string -> address
(** Creates an address of name given in argument*)

val address_of_parameter : int -> address
(** Gets the address of parameter of number given in argument*)

val string_of_address : address -> string
(** Gets a string representation of an address*)

(** The possible right values of the code.*)
type r_value = Name of address | Int of int | Float of float | Bool of bool

type array_address = address * r_value
(** The address of a cell of an array.*)

(** Binary operations*)
type binop =
  | Add_i
  | Sub_i
  | Mul_i
  | Div_i
  | Mod_i
  | Add_f
  | Sub_f
  | Mul_f
  | Div_f
  | Mod_f
  | And
  | Or
  | Eq
  | Neq
  | Lt
  | Gt
  | Leq
  | Geq

type unop = UMin | UMin_f | Not  (** Unary operations*)

(** Type for three address instructions*)
type instruction =
  | Binop of address * binop * r_value * r_value
      (** [Binop(a,op,b,c)] is a = b op c*)
  | Unop of address * unop * r_value  (** [Unop(a,op,b)] is a = op b*)
  | Copy of address * r_value  (** [Copy(a,v)] is a = v*)
  | ADecl of address * r_value
      (** [ADecl(a,v)] reserves an array of size [v] in address [a]. Sets [a.size]*)
  | ACopy of array_address * r_value  (** [ACopy((tab,p),v)] is tab[p] = v*)
  | ALoad of address * array_address  (** [ALoad(a,(tab,p))] is v = tab[p]*)
  | AddressOf of address * address
      (** [AddressOf(tgt,src)] is tgt = &src, i.e., gets the address where src is stored.*)
  | SetPointed of address * r_value
      (** [SetPointed(tgt,src)] is *tgt = src, i.e., set the pointed memory cell.*)
  | GetPointed of address * address
      (** [GetPointed(tgt,src)] is tgt = *src, i.e., gets the value pointed by src.*)
  | Goto of label  (** [Goto l] jumps to label [l]*)
  | IfTrue of r_value * label
      (** [IfTrue(v,l)] jumps to label [l] if [v] is true*)
  | IfFalse of r_value * label
      (** [IfFalse(v,l)] jumps to label [l] if [v] is false*)
  | Param of address  (** [Param a] pushes address [a] to stack of parameters *)
  | Call of label * int
      (** [Call(l,n)] jumps to label l, and after returning, pops n parameters from the stack of parameters*)
  | Noop  (** Does nothing*)
  | Return  (** Return to last [Call] instruction.*)
  | Print_int of r_value  (** Prints a value if it is an Int.*)
  | Print_float of r_value  (** Prints a value if it is an Float.*)
  | Print_bool of r_value  (** Prints a value if it is an Bool.*)
  | Print of string  (** Printf a string.*)

type labelled_instruction = label * instruction
(** Type for an instruction with a label*)

val pp_program : Format.formatter -> labelled_instruction list -> unit
(** Pretty printer for a program, i.e., a labelled instruction list.*)