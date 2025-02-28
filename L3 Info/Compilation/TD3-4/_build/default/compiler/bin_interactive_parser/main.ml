module Command_line = struct
  let from_file = ref true
  let display_parsing = ref true
  let arguments = ref []

  let arg_spec_list =
    [
      ( "-from-stdin",
        Arg.Clear from_file,
        "if present, the argument is a string to parse, otherwise, it is a \
         file name containing the program" );
      ( "-no-interactive",
        Arg.Clear display_parsing,
        "if present, does not show the visualisation of the parsing" );
    ]

  let usage_msg =
    "Usage: " ^ Sys.argv.(0)
    ^ " [program name]\n\
       Parses the program passed in argument (by default, a file). Might be \
       used on expressions, instructions or full programs.\n\
       Executes the program parsed afterwards\n"

  let parse () =
    let filename = ref None in
    Arg.parse (Arg.align arg_spec_list)
      (fun a ->
        match !filename with
        | None -> filename := Some a
        | Some _ -> arguments := a :: !arguments)
      usage_msg;
    match !filename with
    | Some a -> (a, List.rev !arguments)
    | None ->
        Arg.usage arg_spec_list usage_msg;
        exit 0
end

let parse_arguments_var list =
  let list =
    List.map
      (fun s ->
        let l = String.split_on_char ':' s in
        (List.hd l, List.hd (List.tl l)))
      list
  in
  let env = Util.Environment.new_environment () in
  List.iter
    (fun (n, a) -> Abstract_machine.parse_complex_argument_and_affect env n a)
    list;
  env

let arg, arguments = Command_line.parse ()

module Parser_sign = struct
  type value_parsed = Course_language.Ast.t

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Course_language.Lexer
  module Parser = Course_language.Parser
end

module Grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Course_language.Cmly.read "Parser.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module Parser = Cairn.Parsing.MakeWithDefaultMessage (Parser_sign) (Grammar)

let text, lexbuf =
  if !Command_line.from_file then MenhirLib.LexerUtil.read arg
  else (arg, Lexing.from_string arg)

let program =
  if !Command_line.display_parsing then Parser.parse_interactive text lexbuf
  else Some (Course_language.Parser.main Course_language.Lexer.token lexbuf)

let () =
  match program with
  | None -> Format.printf "No program generated. Exiting\n"
  | Some prg -> (
      Format.printf "@[<v 2>Program parsed:@,";
      (match prg with
      | Expression e ->
          Format.printf "@[<v 0>Expression:@,%s@,@]"
            (Course_language.Ast.string_of_expr e)
      | Instruction i ->
          Format.printf "@[<v 0>Instruction:@,%a@,@]"
            Course_language.Ast.pp_instruction i
      | Program p ->
          Format.printf "@[<v 0>Program:@,";
          List.iter (Format.printf "%a" Course_language.Ast.pp_func_decl) p;
          Format.printf "@]");
      Format.printf "@]@,";
      match prg with
      | Instruction instr ->
          let env = parse_arguments_var arguments in
          Format.printf "@[<v 0>Initial Environment:@,%a@,"
            Abstract_machine.pp_value_environment env;
          Course_language.Interpreter.interpret_instruction env
            (Util.Environment.new_environment ())
            instr;
          Format.printf "@[<v 2>Environment after execution:@,%a@,@]"
            Abstract_machine.pp_value_environment env
      | Expression expr ->
          let env = parse_arguments_var arguments in
          Format.printf "@[<v 0>Initial Environment:@,%a@,"
            Abstract_machine.pp_value_environment env;
          Format.printf "@[<v 2>Value of expression:@,%s@,@]"
            (Abstract_machine.string_of_value
               (Course_language.Interpreter.interpret_expr env
                  (Util.Environment.new_environment ())
                  expr))
      | Program prg ->
          Format.printf "@[<v 0>Execution:@,";
          Course_language.Interpreter.interpret_prg prg arguments;
          Format.printf "@]")
