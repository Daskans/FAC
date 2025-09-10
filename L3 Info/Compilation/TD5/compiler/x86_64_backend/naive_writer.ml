open Three_address.Ast
open X86_64_util

type variable_mapping = {
  mutable num_fields : int;
  mapping : (Three_address.Ast.address, address) Hashtbl.t;
}

let get_address_and_update mapping name =
  match Hashtbl.find_opt mapping.mapping name with
  | Some add -> add
  | None ->
      let res = Pointed (Rbp, mapping.num_fields) in
      Hashtbl.add mapping.mapping name res;
      mapping.num_fields <- mapping.num_fields + 8;
      res

let get_address mapping name =
  match name with
  | Local "#result#" -> Register Rax
  | Local _ -> Hashtbl.find mapping.mapping name
  | Parameter num -> Pointed (Rbp, (8 * num) + 16)

let set_value mapping value name =
  match name with
  | Local "#result#" -> [ Movq (value, Register Rax) ]
  | Local _ -> (
      match Hashtbl.find_opt mapping.mapping name with
      | Some add -> [ Movq (value, add) ]
      | None ->
          mapping.num_fields <- mapping.num_fields + 8;
          let add = Pointed (Rbp, -mapping.num_fields) in
          Hashtbl.add mapping.mapping name add;
          [ Movq (value, add) ])
  | Parameter num -> [ Movq (value, Pointed (Rbp, (8 * num) + 16)) ]

type string_mapping = {
  mutable num_strings : int;
  mapping : (string, int) Hashtbl.t;
}

let get_string_label mapping string =
  match Hashtbl.find_opt mapping.mapping string with
  | Some num -> Format.sprintf "__str_%d" num
  | None ->
      Hashtbl.add mapping.mapping string mapping.num_strings;
      let res = Format.sprintf "__str_%d" mapping.num_strings in
      mapping.num_strings <- mapping.num_strings + 1;
      res

let get_string_length mapping string =
  Format.sprintf "%s_len" (get_string_label mapping string)

let write_string_constants fmt mapping =
  Hashtbl.iter
    (fun str _ ->
      let lbl = get_string_label mapping str in
      let len = get_string_length mapping str in
      Format.fprintf fmt "@[<v 4>%s:@,.ascii \"%s\"@,%s = . - %s@]@," lbl
        (String.escaped str) len lbl)
    mapping.mapping

let get_fresh_label label_generator =
  label_generator := !label_generator + 1;
  Format.sprintf "__JumpLbl_%d" !label_generator

let asm_value_of_r_value variables_mapping = function
  | Int v -> Int_cst v
  | Float v -> Float_cst v
  | Bool b -> Int_cst (if b then 1 else 0)
  | Name n ->
      let d = get_address variables_mapping n in
      d

let asm_op_of_op label_generator op src =
  match op with
  | Add_i -> [ Addq (src, Register Rax) ]
  | Sub_i -> [ Subq (src, Register Rax) ]
  | Mul_i -> [ Mulq (src, Register Rax) ]
  | Div_i -> [ Movq (src, Register Rbx); Cqo; Divq (Register Rbx) ]
  | Mod_i ->
      [
        Movq (src, Register Rbx);
        Cqo;
        Divq (Register Rbx);
        Movq (Register Rdx, Register Rax);
      ]
  | Eq ->
      let lbl = get_fresh_label label_generator in
      [
        Cmp (src, Register Rax);
        Movq (Int_cst 1, Register Rax);
        Je lbl;
        Movq (Int_cst 0, Register Rax);
        Label lbl;
      ]
  | Neq ->
      let lbl = get_fresh_label label_generator in
      [
        Cmp (src, Register Rax);
        Movq (Int_cst 1, Register Rax);
        Jne lbl;
        Movq (Int_cst 0, Register Rax);
        Label lbl;
      ]
  | Lt ->
      let lbl = get_fresh_label label_generator in
      [
        Cmp (src, Register Rax);
        Movq (Int_cst 1, Register Rax);
        Jl lbl;
        Movq (Int_cst 0, Register Rax);
        Label lbl;
      ]
  | Leq ->
      let lbl = get_fresh_label label_generator in
      [
        Cmp (src, Register Rax);
        Movq (Int_cst 1, Register Rax);
        Jle lbl;
        Movq (Int_cst 0, Register Rax);
        Label lbl;
      ]
  | Gt ->
      let lbl = get_fresh_label label_generator in
      [
        Cmp (src, Register Rax);
        Movq (Int_cst 1, Register Rax);
        Jg lbl;
        Movq (Int_cst 0, Register Rax);
        Label lbl;
      ]
  | Geq ->
      let lbl = get_fresh_label label_generator in
      [
        Cmp (src, Register Rax);
        Movq (Int_cst 1, Register Rax);
        Jge lbl;
        Movq (Int_cst 0, Register Rax);
        Label lbl;
      ]
  | And -> [ Andq (src, Register Rax) ]
  | Or -> [ Orq (src, Register Rax) ]
  | _ -> [ Todo ]

let asm_op_of_unop op src =
  match op with
  | UMin -> Subq (src, Register Rax)
  | Not -> Subq (src, Register Rax)
  | _ -> Todo

let asm_of_three_address_instruction variables_mapping string_mapping
    label_generator = function
  | Binop (dest, op, src_1, src_2) ->
      let head =
        Movq (asm_value_of_r_value variables_mapping src_1, Register Rax)
      in
      let second =
        asm_op_of_op label_generator op
          (asm_value_of_r_value variables_mapping src_2)
      in
      (head :: second) @ set_value variables_mapping (Register Rax) dest
  | Unop (dest, op, src) ->
      let head =
        Movq
          ( (match op with
            | UMin -> Int_cst 0
            | UMin_f -> Float_cst 0.
            | Not -> Int_cst 1),
            Register Rax )
      in
      head
      :: asm_op_of_unop op (asm_value_of_r_value variables_mapping src)
      :: set_value variables_mapping (Register Rax) dest
  | Copy (dest, src) ->
      Movq (asm_value_of_r_value variables_mapping src, Register Rax)
      :: set_value variables_mapping (Register Rax) dest
  | ADecl _ -> [ Todo ]
  | ACopy _ -> [ Todo ]
  | ALoad _ -> [ Todo ]
  | AddressOf (dest, src) -> (
      match get_address variables_mapping src with
      | Pointed (r, shift) ->
          let hd = set_value variables_mapping (Register r) dest in
          hd @ [ Addq (Int_cst shift, get_address variables_mapping dest) ]
      | _ -> failwith "oups")
  | SetPointed (dest, value) ->
      [
        Movq (get_address variables_mapping dest, Register Rax);
        Movq (asm_value_of_r_value variables_mapping value, Register Rbx);
        Movq (Register Rbx, Pointed (Rax, 0));
      ]
  | GetPointed (dest, src) ->
      let hd =
        [
          Movq (get_address variables_mapping src, Register Rax);
          Movq (Pointed (Rax, 0), Register Rax);
        ]
      in
      hd @ set_value variables_mapping (Register Rax) dest
  | Goto lbl -> [ Jmp (string_of_label lbl) ]
  | IfTrue (value, lbl) ->
      [
        Movq (asm_value_of_r_value variables_mapping value, Register Rax);
        Cmp (Int_cst 0, Register Rax);
        Jne (string_of_label lbl);
      ]
  | IfFalse (value, lbl) ->
      [
        Movq (asm_value_of_r_value variables_mapping value, Register Rax);
        Cmp (Int_cst 0, Register Rax);
        Je (string_of_label lbl);
      ]
  | Param arg -> [ Pushq (get_address variables_mapping arg) ]
  | Call (lbl, num) ->
      [ Call (string_of_label lbl); Subq (Int_cst (num * 8), Register Rsp) ]
  | Noop -> []
  | Return -> [ Leave; Ret ]
  | Print str ->
      let lbl = get_string_label string_mapping str in
      let str_len = get_string_length string_mapping str in
      [
        Movq (Int_cst 1, Register Rax);
        Movq (Int_cst 1, Register Rdi);
        Movq (Label_cst lbl, Register Rsi);
        Movq (Label_cst str_len, Register Rdx);
        Syscall;
      ]
  | _ -> [ Todo ]
