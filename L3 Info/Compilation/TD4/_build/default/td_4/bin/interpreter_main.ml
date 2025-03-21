module CommandLine = struct
  let only_display = ref false

  let arg_spec_list =
    [
      ( "-display",
        Arg.Set only_display,
        " if present, the expression/instruction/program corresponding to the \
         input will only be displayed" );
    ]

  let usage_msg = "Usage: " ^ Sys.argv.(0) ^ " [program name]\n"

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
    | None -> Arg.usage arg_spec_list usage_msg; exit 0
end

let filename = CommandLine.parse ()

let interpret_expr expr environnement funct =
  Format.printf "@[<v 0>Functions known:@,%a@,"
    Interpreter.AbstractMachine.FunctionsEnvironment.pp_environment funct;
  Format.printf "Starting environment:@,%a@,"
    Interpreter.AbstractMachine.Environment.pp_environment environnement;
  if !CommandLine.only_display then
    Format.printf "Expression : %s@,@]" (Ast.string_of_expr expr)
  else
    let result = Interpreter.interpret_expr environnement funct expr in
    Format.printf "value of %s : %s@," (Ast.string_of_expr expr)
      (Interpreter.AbstractMachine.string_of_value result);
    Format.printf "End environment:@,%a@,@]"
      Interpreter.AbstractMachine.Environment.pp_environment environnement

let interpret_instr instr environnement funct =
  Format.printf "@[<v 0>Functions known:@,%a@,"
    Interpreter.AbstractMachine.FunctionsEnvironment.pp_environment funct;
  Format.printf "Initial environment:@,%a@,@,Instruction: @,%a @,@,"
    Interpreter.AbstractMachine.Environment.pp_environment environnement
    Ast.pp_instruction instr;
  if not !CommandLine.only_display then (
    Interpreter.interpret_instruction environnement funct instr;
    Format.printf "yields environment:@,%a@,@]"
      Interpreter.AbstractMachine.Environment.pp_environment environnement)
  else Format.printf "@]"

let interpret_prg prg =
  Format.printf "@[<v 0>Program :@,";
  List.iter (Format.printf "%a@,@," Ast.pp_func_decl) prg;
  if not !CommandLine.only_display then (
    Format.printf "Output:@,%!";
    Interpreter.interpret_prg prg);
  Format.printf "@,@]"

let file = open_in filename
let ic = Lexing.from_channel file
let prg = Language_parser.Parser.main (Language_parser.Lexer.token) ic
let () = close_in file

let () = match prg with
  | Language_parser.Result_parser.Program p -> interpret_prg p
  | Language_parser.Result_parser.Instruction i -> interpret_instr i (Interpreter.AbstractMachine.Environment.new_environnement ()) (Interpreter.AbstractMachine.FunctionsEnvironment.initial_functions_list ())
  | Language_parser.Result_parser.Expression e -> interpret_expr e (Interpreter.AbstractMachine.Environment.new_environnement ()) (Interpreter.AbstractMachine.FunctionsEnvironment.initial_functions_list ())
