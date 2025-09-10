type label = string

let label_of_string s = s
let string_of_label s = s
let no_label = ""

type address = Local of string | Parameter of int

let address_of_string s = Local s
let address_of_parameter i = Parameter i

let string_of_address = function
  | Local string -> string
  | Parameter int -> Format.sprintf "#arg_%d#" int

type r_value = Name of address | Int of int | Float of float | Bool of bool
type array_address = address * r_value

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

type unop = UMin | UMin_f | Not

type instruction =
  | Binop of address * binop * r_value * r_value
  | Unop of address * unop * r_value
  | Copy of address * r_value
  | ADecl of address * r_value
  | ACopy of array_address * r_value
  | ALoad of address * array_address
  | AddressOf of address * address
  | SetPointed of address * r_value
  | GetPointed of address * address
  | Goto of label
  | IfTrue of r_value * label
  | IfFalse of r_value * label
  | Param of address
  | Call of label * int
  | Noop
  | Return
  | Print_int of r_value
  | Print_float of r_value
  | Print_bool of r_value
  | Print of string

type labelled_instruction = label * instruction

let string_of_value = function
  | Name address -> string_of_address address
  | Int int -> string_of_int int
  | Float float -> string_of_float float
  | Bool bool -> if bool then "true" else "false"

let string_of_binop = function
  | Add_i -> "+"
  | Sub_i -> "-"
  | Mul_i -> "*"
  | Div_i -> "/"
  | Mod_i -> "%"
  | Add_f -> "+."
  | Sub_f -> "-."
  | Mul_f -> "*."
  | Div_f -> "/."
  | Mod_f -> "%."
  | And -> "&&"
  | Or -> "||"
  | Eq -> "="
  | Neq -> "<>"
  | Lt -> "<"
  | Gt -> ">"
  | Leq -> "<="
  | Geq -> ">="

let string_of_unop = function
  | UMin -> "UMin"
  | UMin_f -> "UMin_f"
  | Not -> "Not"

let string_of_instruction = function
  | Binop (address, binop, value1, value2) ->
      Format.sprintf "Binop(%s,%s,%s,%s)"
        (string_of_address address)
        (string_of_binop binop) (string_of_value value1)
        (string_of_value value2)
  | Unop (address, unop, value) ->
      Format.sprintf "Unop(%s,%s,%s)"
        (string_of_address address)
        (string_of_unop unop) (string_of_value value)
  | Copy (address, value) ->
      Format.sprintf "Copy(%s,%s)"
        (string_of_address address)
        (string_of_value value)
  | ADecl (address, value) ->
      Format.sprintf "ADecl(%s,%s)"
        (string_of_address address)
        (string_of_value value)
  | ACopy ((array, pos), value) ->
      Format.sprintf "ACopy(%s[%s],%s)" (string_of_address array)
        (string_of_value pos) (string_of_value value)
  | ALoad (address, (array, pos)) ->
      Format.sprintf "ALoad(%s,%s[%s])"
        (string_of_address address)
        (string_of_address array) (string_of_value pos)
  | AddressOf (tgt, src) ->
      Format.sprintf "AddressOf(%s,%s)" (string_of_address tgt)
        (string_of_address src)
  | SetPointed (tgt, src) ->
      Format.sprintf "SetPointed(%s,%s)" (string_of_address tgt)
        (string_of_value src)
  | GetPointed (tgt, src) ->
      Format.sprintf "GetPointed(%s,%s)" (string_of_address tgt)
        (string_of_address src)
  | Goto label -> Format.sprintf "Goto %s" label
  | IfTrue (value, label) ->
      Format.sprintf "IfTrue(%s) Goto %s" (string_of_value value) label
  | IfFalse (value, label) ->
      Format.sprintf "IfFalse(%s) Goto %s" (string_of_value value) label
  | Param address -> Format.sprintf "Param %s" (string_of_address address)
  | Call (label, int) -> Format.sprintf "Call(%s,%d)" label int
  | Noop -> "Noop"
  | Return -> "Return"
  | Print_int value -> Format.sprintf "Print_int %s" (string_of_value value)
  | Print_float value -> Format.sprintf "Print_float %s" (string_of_value value)
  | Print_bool value -> Format.sprintf "Print_bool %s" (string_of_value value)
  | Print string -> Format.sprintf "Print %s" (String.escaped string)

let pp_program fmt prg =
  Format.fprintf fmt "@[<v 0>";
  List.iter
    (fun (lbl, instr) ->
      Format.fprintf fmt "%s%s@,"
        (if lbl <> "" then lbl ^ " : " else "")
        (string_of_instruction instr))
    prg;
  Format.fprintf fmt "@]@,"
