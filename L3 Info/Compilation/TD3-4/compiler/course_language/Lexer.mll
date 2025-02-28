

{
    open Parser
    exception Error of string
}

let digit = ['0'-'9']
let alphanum = ['a'-'z' 'A'-'Z' '0'-'9' '\'' '_']

rule token = parse
    | "//" [^ '\n']* '\n' {Lexing.new_line lexbuf; token lexbuf}
    | "/*"              {commentary lexbuf}
    | [' ' '\t' '\r']   {token lexbuf}
    | '\n'              { Lexing.new_line lexbuf ; token lexbuf }
    | "if"              { IF }
    | "then"            { THEN }
    | "else"            { ELSE }
    | "while"           { WHILE }
    | "+"               { ADD }
    | "-"               { SUB }
    | "*"               { MUL }
    | "/"               { DIV }
    | "%"               { MOD }
    | "&&"              { AND }
    | "||"              { OR }
    | "!"               { NOT }
    | "="               { EQ }
    | "<>"              { NEQ }
    | "<="              { LEQ }
    | ">="              { GEQ }
    | "<"               { LT }
    | ">"               { GT }
    | "["               { L_SQ_BRK }
    | "]"               { R_SQ_BRK }
    | "("               { L_PAR }
    | ")"               { R_PAR }
    | "{"               { L_CUR_BRK }
    | "}"               { R_CUR_BRK }
    | ";"               { SEMICOLON }
    | "int"             { INT_TYP }
    | "float"           { FLOAT_TYP }
    | "bool"            { BOOL_TYP }
    | "null"            { NULL_TYP }
    | "true"            { BOOL(true) }
    | "false"           { BOOL(false) }
    | "print"           { PRINT }
    | "size"            { SIZE }
    | "return"          { RETURN }
    | ":="              { ASSIGN }
    | "::="             { DEF }
    | ","               { COMMA }
    | "."               { DOT }
    | "var"             { VAR }

    | "\"" ([^ '\"']* as s) "\""  { STRING(s) }
    | (digit)* "." (digit)* as s {FLOAT(try float_of_string s with Failure _ -> raise (Error(s)) )}
    | (digit)+ as s     { INT(try int_of_string s with Failure _ ->(let pos = Lexing.lexeme_start_p lexbuf in raise (Error(Format.sprintf "Line %d, char %d ,Read: '%s'. It is not a valid integer" pos.pos_lnum (pos.pos_cnum - pos.pos_bol +1) s)) ))}
    | eof               { EOF }
    | ['a'-'z' 'A'-'Z'] (alphanum)* as s  { ID(s) }
    | _ as s            { let pos = Lexing.lexeme_start_p lexbuf in raise (Error(Format.sprintf "Line %d, char %d ,Read: '%c'. It is not an acceptable character" pos.pos_lnum (pos.pos_cnum - pos.pos_bol +1) s)) }

and commentary = parse
    | '\n'      {Lexing.new_line lexbuf; commentary lexbuf}
    | "*/"      { token lexbuf }
    | _ { commentary lexbuf }