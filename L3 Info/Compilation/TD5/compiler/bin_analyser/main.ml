module CommandLine = struct
  let execute = ref false
  let simplify = ref true
  let analyse = ref true
  let from_file = ref true
  let three_address = ref false

  let arg_spec_list =
    [
      ( "-from-stdin",
        Arg.Clear from_file,
        "if present, the argument is a string to parse, otherwise, it is a \
         file name containing the program" );
      ( "-execute",
        Arg.Set execute,
        " if present, the expression/instruction/program corresponding to the \
         input will be executed after analysis" );
      ("-no-analysis", Arg.Clear analyse, "if present, skips the type analysis");
      ( "-no-simplification",
        Arg.Clear simplify,
        "if present, skips the simplification" );
      ( "-three-address",
        Arg.Set three_address,
        "if present, translate the program to three address code and executes \
         it" );
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
      if !CommandLine.execute then (
        let env = Util.Environment.new_environment () in
        Course_language.Interpreter.interpret_instruction env
          (Util.Environment.new_environment ())
          instr;
        Format.printf "@[<v 2>Environment after execution:@,%a@,@]"
          Abstract_machine.pp_value_environment env);
      if !CommandLine.three_address then (
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
        Format.printf "@[<v 1>3 Address translation:@,%a@]"
          Three_address.Ast.pp_program code;
        Format.printf "Execution of 3 address :\n%!";
        Three_address.Interpreter.execute_prg
          (code @ [ (Three_address.Ast.label_of_string "", Return) ]))
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
      if !CommandLine.execute then
        Format.printf
          "@[<v 2>Value of expression on empty environments :@,%s@,@]"
          (Abstract_machine.string_of_value
             (Course_language.Interpreter.interpret_expr
                (Util.Environment.new_environment ())
                (Util.Environment.new_environment ())
                expr));
      if !CommandLine.three_address then (
        let counter =
          Three_address.Course_language_to_three_address.Counter.create ()
        in
        let mapper =
          Three_address.Course_language_to_three_address.Arg_mapper.create ()
        in
        let _, code =
          Three_address.Course_language_to_three_address.expr_to_code counter
            mapper expr
        in
        Format.printf "@[<v 1>3 Address translation:@,%a@]"
          Three_address.Ast.pp_program code;
        Format.printf "Execution of 3 address :\n%!";
        Three_address.Interpreter.execute_prg code)
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
      if !CommandLine.execute then (
        Format.printf "@[<v 0>Execution:@,";
        Course_language.Interpreter.interpret_prg prg [];
        Format.printf "@]");
      if !CommandLine.three_address then (
        let code =
          Three_address.(Ast.no_label, Ast.Goto (Ast.label_of_string "main"))
          :: Three_address.Course_language_to_three_address.program_to_code prg
        in
        Format.printf "@[<v 1>3 Address translation:@,%a@]"
          Three_address.Ast.pp_program code;
        Format.printf "Execution of 3 address :\n%!";
        Three_address.Interpreter.execute_prg code)
