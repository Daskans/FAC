module CommandLine = struct
  type parser =
    | First
    | Dyck_naive
    | Dyck_left
    | Dyck_right
    | Dyck_epsilon_left
    | Dyck_epsilon_right
    | Program
    | Eee
    | Etf
    | Custom

  let parser = ref First

  let string_of_task = function
    | First -> "first"
    | Dyck_naive -> "Dyck_naive"
    | Dyck_left -> "Dyck_left"
    | Dyck_right -> "Dyck_right"
    | Dyck_epsilon_left -> "Dyck_epsilon_left"
    | Dyck_epsilon_right -> "Dyck_epsilon_right"
    | Program -> "Program"
    | Eee -> "Eee"
    | Etf -> "Etf"
    | Custom -> "Custom"

  let task_of_string = function
    | "first" -> First
    | "Dyck_naive" -> Dyck_naive
    | "Dyck_left" -> Dyck_left
    | "Dyck_right" -> Dyck_right
    | "Dyck_epsilon_left" -> Dyck_epsilon_left
    | "Dyck_epsilon_right" -> Dyck_epsilon_right
    | "Program" -> Program
    | "Eee" -> Eee
    | "Etf" -> Etf
    | "Custom" -> Custom
    | _ -> failwith "wrong task string"

  let parse_from_file = ref false

  let arg_spec_list =
    [
      ( "-parser",
        Arg.Symbol
          ( [
              "first";
              "Custom";
              "Dyck_naive";
              "Dyck_left";
              "Dyck_right";
              "Dyck_epsilon_left";
              "Dyck_epsilon_right";
              "Eee";
              "Etf";
              "Program";
            ],
            fun s -> parser := task_of_string s ),
        " determines which parser is used for parsing the input."
        ^ " (default: " ^ string_of_task !parser ^ ")" );
      ( "-from-file",
        Arg.Set parse_from_file,
        " if present, the argument is a filename, otherwise it is the string \
         to parse." );
    ]

  let usage_msg =
    "Usage: " ^ Sys.argv.(0)
    ^ " [argument]\n\
       Parses the argument with the selected parser and displays the execution \
       of the parser step by step.\n\
       [argument] is either the string to parse or the filename to be analysed \
       (if [-from-file] is present)\n"

  let parse () =
    let res = ref None in
    Arg.parse (Arg.align arg_spec_list)
      (fun a ->
        match !res with
        | None -> res := Some a
        | Some _ -> raise (Arg.Bad "Got too many inputs"))
      usage_msg;
    match !res with
    | None ->
        Arg.usage arg_spec_list usage_msg;
        exit 0
    | Some s -> s
end

let str = CommandLine.parse ()

module First_Parser_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = unit = struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = First_parser.Lexer
  module Parser = First_parser.Parser
end

module First_Parser_Grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (First_parser.Cmly.read "Parser.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module PFirst =
  Cairn.Parsing.MakeWithDefaultMessage
    (First_Parser_Sign)
    (First_Parser_Grammar)

module Custom_Parser_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = unit = struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Custom_parser.Lexer
  module Parser = Custom_parser.Parser
end

module Custom_Parser_Grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Custom_parser.Cmly.read "Parser.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module PCustom =
  Cairn.Parsing.MakeWithDefaultMessage
    (Custom_Parser_Sign)
    (Custom_Parser_Grammar)

module Dyck_simple_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = unit = struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Dyck_parser.Lexer
  module Parser = Dyck_parser.Dyck_simple
end

module Dyck_simple_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Dyck_parser.Cmly.read "Dyck_simple.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module PSimple =
  Cairn.Parsing.MakeWithDefaultMessage (Dyck_simple_Sign) (Dyck_simple_grammar)

module Dyck_left_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = unit = struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Dyck_parser.Lexer
  module Parser = Dyck_parser.Dyck_left
end

module Dyck_left_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Dyck_parser.Cmly.read "Dyck_left.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module PLeft =
  Cairn.Parsing.MakeWithDefaultMessage (Dyck_left_Sign) (Dyck_left_grammar)

module Dyck_right_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = unit = struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Dyck_parser.Lexer
  module Parser = Dyck_parser.Dyck_right
end

module Dyck_right_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Dyck_parser.Cmly.read "Dyck_right.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module PRight =
  Cairn.Parsing.MakeWithDefaultMessage (Dyck_right_Sign) (Dyck_right_grammar)

module Dyck_epsilon_left_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = unit = struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Dyck_parser.Lexer
  module Parser = Dyck_parser.Dyck_epsilon_left
end

module Dyck_epsilon_left_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Dyck_parser.Cmly.read "Dyck_epsilon_left.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module PEpsLeft =
  Cairn.Parsing.MakeWithDefaultMessage
    (Dyck_epsilon_left_Sign)
    (Dyck_epsilon_left_grammar)

module Dyck_epsilon_right_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = unit = struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Dyck_parser.Lexer
  module Parser = Dyck_parser.Dyck_epsilon_right
end

module Dyck_epsilon_right_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content =
    Option.get (Dyck_parser.Cmly.read "Dyck_epsilon_right.cmly")

  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module PEpsRight =
  Cairn.Parsing.MakeWithDefaultMessage
    (Dyck_epsilon_right_Sign)
    (Dyck_epsilon_right_grammar)

module Eee_sign : Cairn.Parsing.parser_decorated with type value_parsed = unit =
struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Eee_parser.Lexer
  module Parser = Eee_parser.Parser
end

module Eee_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Eee_parser.Cmly.read "Parser.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module Eee_parser =
  Cairn.Parsing.MakeWithDefaultMessage (Eee_sign) (Eee_grammar)

module Etf_sign : Cairn.Parsing.parser_decorated with type value_parsed = unit =
struct
  type value_parsed = unit

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Etf_parser.Lexer
  module Parser = Etf_parser.Parser
end

module Etf_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Etf_parser.Cmly.read "Parser.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module Etf_parser =
  Cairn.Parsing.MakeWithDefaultMessage (Etf_sign) (Etf_grammar)

module Language_Sign :
  Cairn.Parsing.parser_decorated with type value_parsed = Course_language.Ast.t =
struct
  type value_parsed = Course_language.Ast.t

  let error_strategy = Cairn.Parsing.Stop

  module Lexer = Course_language.Lexer
  module Parser = Course_language.Parser
end

module Language_grammar = MenhirSdk.Cmly_read.Lift (struct
  let file_content = Option.get (Course_language.Cmly.read "Parser.cmly")
  let prefix = "CMLY" ^ MenhirSdk.Version.version
  let grammar = Marshal.from_string file_content (String.length prefix)
end)

module ProgParser =
  Cairn.Parsing.MakeWithDefaultMessage (Language_Sign) (Language_grammar)

let parse =
  match !CommandLine.parser with
  | First -> PFirst.parse_interactive
  | Custom -> PCustom.parse_interactive
  | Dyck_naive -> PSimple.parse_interactive
  | Dyck_left -> PLeft.parse_interactive
  | Dyck_right -> PRight.parse_interactive
  | Dyck_epsilon_left -> PEpsLeft.parse_interactive
  | Dyck_epsilon_right -> PEpsRight.parse_interactive
  | Eee -> Eee_parser.parse_interactive
  | Etf -> Etf_parser.parse_interactive
  | Program ->
      fun text lexbuf ->
        let _ = ProgParser.parse_interactive text lexbuf in
        Some ()

let _ =
  let text, lexbuf =
    if !CommandLine.parse_from_file then MenhirLib.LexerUtil.read str
    else (str, Lexing.from_string str)
  in
  parse text lexbuf
