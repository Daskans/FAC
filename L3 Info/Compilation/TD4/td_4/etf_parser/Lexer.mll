{
    open Parser
    exception Error of string
}

let digit = ['0'-'9']
let integer = digit+
let reciprocal = "^-1"

rule token = parse
    | "//" [^ '\n']* '\n' {token lexbuf}
    | ("/*" ([^ '*' '/'] | ('*'[^ '/']) | ([^ '*'] '/'))* "*/" |"/*/") {token lexbuf}
    | [' ' '\t' '\r']   {token lexbuf}
    | '\n'              { Lexing.new_line lexbuf ; token lexbuf }
    | "+"               { ADD }
    | "-"               { SUB }
    | reciprocal        { REC }
    | "*"               { MUL }
    | "/"               { DIV }
    | "("               { LPAR }
    | ")"               { RPAR }
    | integer as i      { INT(try int_of_string i with Failure _ -> raise (Error(i)) )}
    | eof               { EOF }
    | _ as s            { let pos = Lexing.lexeme_start_p lexbuf in raise (Error(Format.sprintf "Line %d, char %d ,Read: '%c'. It is not an acceptable character" pos.pos_lnum (pos.pos_cnum - pos.pos_bol +1) s)) }
