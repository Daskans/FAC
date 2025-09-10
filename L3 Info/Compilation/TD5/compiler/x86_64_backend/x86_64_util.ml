type register =
  | Rax
  | Rbx
  | Rcx
  | Rsp
  | Rbp
  | Rdi
  | Rsi
  | Rdx
  | R8
  | R9
  | R10
  | R11
  | R12
  | R13
  | R14
  | R15

let string_of_register = function
  | Rax -> "%rax"
  | Rbx -> "%rbx"
  | Rcx -> "%rcx"
  | Rsp -> "%rsp"
  | Rbp -> "%rbp"
  | Rdi -> "%rdi"
  | Rsi -> "%rsi"
  | Rdx -> "%rdx"
  | R8 -> "%r8"
  | R9 -> "%r9"
  | R10 -> "%r10"
  | R11 -> "%r11"
  | R12 -> "%r12"
  | R13 -> "%r13"
  | R14 -> "%r14"
  | R15 -> "%r15"

type address =
  | Register of register
  | Pointed of register * int
  | Int_cst of int
  | Float_cst of float
  | Label_cst of string

let string_of_address = function
  | Register r -> string_of_register r
  | Pointed (r, shift) ->
      (if shift <> 0 then Format.sprintf "%d" shift else "")
      ^ Format.sprintf "(%s)" (string_of_register r)
  | Int_cst i -> Format.sprintf "$%d" i
  | Float_cst f -> Format.sprintf "%f" f
  | Label_cst s -> Format.sprintf "$%s" s

type asm_instruction =
  | Movq of address * address
  | Addq of address * address
  | Subq of address * address
  | Mulq of address * address
  | Divq of address
  | Andq of address * address
  | Orq of address * address
  | Pushq of address
  | Popq of address
  | Leave
  | Ret
  | Jmp of string
  | Je of string
  | Jne of string
  | Jl of string
  | Jle of string
  | Jg of string
  | Jge of string
  | Cmp of address * address
  | Cqo
  | Call of string
  | Syscall
  | Label of string
  | Todo  (** placeholder instruction to get rid of when complete*)

let string_of_asm_instruction = function
  | Movq (src, tgt) ->
      Format.sprintf "movq %s, %s" (string_of_address src)
        (string_of_address tgt)
  | Addq (src, tgt) ->
      Format.sprintf "addq %s, %s" (string_of_address src)
        (string_of_address tgt)
  | Subq (src, tgt) ->
      Format.sprintf "subq %s, %s" (string_of_address src)
        (string_of_address tgt)
  | Mulq (src, tgt) ->
      Format.sprintf "imulq %s, %s" (string_of_address src)
        (string_of_address tgt)
  | Divq div -> Format.sprintf "idivq %s" (string_of_address div)
  | Andq (src, tgt) ->
      Format.sprintf "andq %s, %s" (string_of_address src)
        (string_of_address tgt)
  | Orq (src, tgt) ->
      Format.sprintf "orq %s, %s" (string_of_address src)
        (string_of_address tgt)
  | Pushq src -> Format.sprintf "pushq %s" (string_of_address src)
  | Popq tgt -> Format.sprintf "popq %s" (string_of_address tgt)
  | Leave -> Format.sprintf "leave"
  | Ret -> Format.sprintf "ret"
  | Jmp lbl -> Format.sprintf "jmp %s" lbl
  | Je lbl -> Format.sprintf "je %s" lbl
  | Jne lbl -> Format.sprintf "jne %s" lbl
  | Jl lbl -> Format.sprintf "jl %s" lbl
  | Jle lbl -> Format.sprintf "jle %s" lbl
  | Jg lbl -> Format.sprintf "jg %s" lbl
  | Jge lbl -> Format.sprintf "jge %s" lbl
  | Cmp (s1, s2) ->
      Format.sprintf "cmpq %s, %s" (string_of_address s1) (string_of_address s2)
  | Cqo -> Format.sprintf "cqo"
  | Call func -> Format.sprintf "call %s" func
  | Syscall -> Format.sprintf "syscall"
  | Label lbl -> Format.sprintf "%s:" lbl
  | Todo -> Format.sprintf "#todo"
