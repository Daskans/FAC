module CommandLine = struct
  let simplify = ref true
  let analyse = ref true
  let from_file = ref true
  let output_file = ref "compiled.out"

  let arg_spec_list =
    [
      ( "-from-stdin",
        Arg.Clear from_file,
        "if present, the argument is a string to parse, otherwise, it is a \
         file name containing the program" );
      ("-no-analysis", Arg.Clear analyse, "if present, skips the type analysis");
      ( "-no-simplification",
        Arg.Clear simplify,
        "if present, skips the simplification" );
      ( "-o",
        Arg.String (fun s -> output_file := s),
        "sets the name of the output file" );
    ]

  let usage_msg =
    "Usage: " ^ Sys.argv.(0)
    ^ " [program name]\n\
       Analyses the program passed in argument, simplifies it, and executes it \
       (depending on options). Might be used on expressions, instructions or \
       full programs.\n"

  let parse () =
    let filename = ref None in
    Arg.parse (Arg.align arg_spec_list)
      (fun a ->
        match !filename with
        | None -> filename := Some a
        | Some _ ->
            raise
              (Arg.Bad
                 ("unexpected argument `" ^ a
                ^ "' (multiple inputs are not allowed)")))
      usage_msg;
    match !filename with
    | Some a -> a
    | None ->
        Arg.usage arg_spec_list usage_msg;
        exit 0
end

let arg = CommandLine.parse ()

let text, ic =
  if !CommandLine.from_file then MenhirLib.LexerUtil.read arg
  else (arg, Lexing.from_string arg)

let prg =
  try Course_language.Parser.main Course_language.Lexer.token ic
  with _ -> failwith "syntax error"

let () =
  let errors = Util.Error_report.create_empty text in
  let env = Util.Environment.new_environment () in
  let init_env = Util.Environment.new_environment () in
  let f_env = Util.Environment.new_environment () in
  match prg with
  | Instruction instr ->
      if !CommandLine.analyse then (
        Course_language.Type_analyser.type_instruction env init_env f_env errors
          instr;
        Format.printf "@[<v 0>Rapport d’erreur@,%a@,"
          Util.Error_report.pp_errors errors);
      let instr =
        if !CommandLine.simplify then (
          let simpl_instr =
            Course_language.Simplifier.simplify_instruction instr
          in
          Format.printf "Simplified instruction:@,%a@,@]"
            Course_language.Ast.pp_instruction simpl_instr;
          simpl_instr)
        else instr
      in
      let counter =
        Three_address.Course_language_to_three_address.Counter.create ()
      in
      let mapper =
        Three_address.Course_language_to_three_address.Arg_mapper.create ()
      in
      let code =
        Three_address.Course_language_to_three_address.instruction_to_code
          counter mapper instr
      in
      let oc = open_out !CommandLine.output_file in
      let fmt = Format.formatter_of_out_channel oc in
      let variable_mapping =
        {
          X86_64_backend.Naive_writer.num_fields = 0;
          mapping = Hashtbl.create 0;
        }
      in
      let string_mapping =
        {
          X86_64_backend.Naive_writer.num_strings = 0;
          mapping = Hashtbl.create 0;
        }
      in
      let label_generator = ref 0 in
      Format.fprintf fmt
        "@[<v 0>@[<v 4>.text@,\
         .globl _start@]@,\
         @[<v 4>_start:@,\
         pushq %%rbp@,\
         movq %%rsp, %%rbp@,";
      List.iter
        (fun (lbl, instr) ->
          if lbl <> Three_address.Ast.no_label then
            Format.fprintf fmt "@]@,@[<v 4>%s:@,"
              (Three_address.Ast.string_of_label lbl)
          else
            List.iter
              (fun asm_instr ->
                Format.fprintf fmt "%s@,"
                  (X86_64_backend.X86_64_util.string_of_asm_instruction
                     asm_instr);
                Format.printf "%s\n"
                  (X86_64_backend.X86_64_util.string_of_asm_instruction
                     asm_instr))
              (X86_64_backend.Naive_writer.asm_of_three_address_instruction
                 variable_mapping string_mapping label_generator instr))
        code;
      Format.fprintf fmt "leave@,movq $60, %%rax@,movq $0, %%rdi@,syscall@]@,";
      Format.fprintf fmt "%a@]"
        X86_64_backend.Naive_writer.write_string_constants string_mapping;
      Format.pp_print_flush fmt ();
      close_out oc
  | Expression expr ->
      if !CommandLine.analyse then (
        let t =
          Course_language.Type_analyser.type_expr env init_env f_env errors expr
        in
        Format.printf "@[<v 0>Final type = %s@,"
          (Course_language.Ast.string_of_type_value t);
        Format.printf "Rapport d’erreur@,%a@,@]" Util.Error_report.pp_errors
          errors);
      let expr =
        if !CommandLine.simplify then (
          let simpl = Course_language.Simplifier.simplify_expr expr in
          Format.printf "@[<v 0>Simplified expr:@,%s@,@]"
            (Course_language.Ast.string_of_expr simpl);
          simpl)
        else expr
      in
      let counter =
        Three_address.Course_language_to_three_address.Counter.create ()
      in
      let mapper =
        Three_address.Course_language_to_three_address.Arg_mapper.create ()
      in
      let value, code =
        Three_address.Course_language_to_three_address.expr_to_code counter
          mapper expr
      in
      let label_generator = ref 0 in
      let oc = open_out !CommandLine.output_file in
      let fmt = Format.formatter_of_out_channel oc in
      let variable_mapping =
        {
          X86_64_backend.Naive_writer.num_fields = 0;
          mapping = Hashtbl.create 0;
        }
      in
      let string_mapping =
        {
          X86_64_backend.Naive_writer.num_strings = 0;
          mapping = Hashtbl.create 0;
        }
      in
      Format.fprintf fmt
        "@[<v 0>@[<v 4>.text@,\
         .globl _start@]@,\
         @[<v 4>_start:@,\
         pushq %%rbp@,\
         movq %%rsp, %%rbp@,";
      List.iter
        (fun (lbl, instr) ->
          if lbl <> Three_address.Ast.no_label then
            Format.fprintf fmt "@]@,@[<v 4>%s@,"
              (Three_address.Ast.string_of_label lbl)
          else
            List.iter
              (fun asm_instr ->
                Format.fprintf fmt "%s@,"
                  (X86_64_backend.X86_64_util.string_of_asm_instruction
                     asm_instr);
                Format.printf "%s\n"
                  (X86_64_backend.X86_64_util.string_of_asm_instruction
                     asm_instr))
              (X86_64_backend.Naive_writer.asm_of_three_address_instruction
                 variable_mapping string_mapping label_generator instr))
        (code
        @ [
            Three_address.Ast.(no_label, Copy (address_of_string "res", value));
          ]);
      Format.fprintf fmt "popq %%rdi@,leave@,movq $60, %%rax@,syscall@]@,@]";
      Format.pp_print_flush fmt ();
      close_out oc
  | Program prg ->
      if !CommandLine.analyse then (
        List.iter
          (Course_language.Type_analyser.type_func_decl f_env errors)
          prg;
        Format.printf "@[<v 0>Rapport d’erreur@,%a@,"
          Util.Error_report.pp_errors errors);
      let prg =
        if !CommandLine.simplify then (
          let prg =
            List.map Course_language.Simplifier.simplify_func_decl prg
          in
          Format.printf "Program parsed (simplified) :@,";
          List.iter (Format.printf "%a@," Course_language.Ast.pp_func_decl) prg;
          prg)
        else prg
      in
      let oc = open_out !CommandLine.output_file in
      let fmt = Format.formatter_of_out_channel oc in
      let string_mapping =
        {
          X86_64_backend.Naive_writer.num_strings = 0;
          mapping = Hashtbl.create 0;
        }
      in
      let label_generator = ref 0 in
      let counter =
        Three_address.Course_language_to_three_address.Counter.create ()
      in
      Format.fprintf fmt
        "@[<v 0>@[<v 4>.text@,\
         .globl _start@]@,\
         @[<v 4>_start:@,\
         call main@,\
         movq $60, %%rax@,\
         movq $0, %%rdi@,\
         syscall@]@,";
      List.iter
        (fun (Course_language.Ast.Func_decl (_, name, _, _, _) as f) ->
          let variable_mapping =
            {
              X86_64_backend.Naive_writer.num_fields = 0;
              mapping = Hashtbl.create 0;
            }
          in
          let three_address_code =
            Three_address.Course_language_to_three_address.function_decl_to_code
              counter f
          in
          Format.fprintf fmt "@[<v 4>%s:@,pushq %%rbp@,movq %%rsp,%%rbp@," name;
          List.iter
            (fun (lbl, inst) ->
              if lbl <> Three_address.Ast.no_label then
                Format.fprintf fmt "@]@,@[<v 4>%s:@,"
                  (Three_address.Ast.string_of_label lbl);
              List.iter
                (fun i ->
                  Format.fprintf fmt "%s@,"
                    (X86_64_backend.X86_64_util.string_of_asm_instruction i))
                (X86_64_backend.Naive_writer.asm_of_three_address_instruction
                   variable_mapping string_mapping label_generator inst))
            (List.tl three_address_code);
          Format.fprintf fmt "@]@,")
        prg;
      Format.fprintf fmt "%a@]"
        X86_64_backend.Naive_writer.write_string_constants string_mapping;
      Format.pp_print_flush fmt ();
      close_out oc