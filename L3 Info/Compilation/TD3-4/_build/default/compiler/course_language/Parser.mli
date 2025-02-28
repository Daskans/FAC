
(* The type of tokens. *)

type token = 
  | WHILE
  | VAR
  | THEN
  | SUB
  | STRING of (string)
  | SIZE
  | SEMICOLON
  | R_SQ_BRK
  | R_PAR
  | R_CUR_BRK
  | RETURN
  | PRINT
  | OR
  | NULL_TYP
  | NOT
  | NEQ
  | MUL
  | MOD
  | L_SQ_BRK
  | L_PAR
  | L_CUR_BRK
  | LT
  | LEQ
  | INT_TYP
  | INT of (int)
  | IF
  | ID of (string)
  | GT
  | GEQ
  | FLOAT_TYP
  | FLOAT of (float)
  | EQ
  | EOF
  | ELSE
  | DOT
  | DIV
  | DEF
  | COMMA
  | BOOL_TYP
  | BOOL of (bool)
  | ASSIGN
  | AND
  | ADD

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val main: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.t)

module MenhirInterpreter : sig
  
  (* The incremental API. *)
  
  include MenhirLib.IncrementalEngine.INCREMENTAL_ENGINE
    with type token = token
  
  (* The indexed type of terminal symbols. *)
  
  type _ terminal = 
    | T_error : unit terminal
    | T_WHILE : unit terminal
    | T_VAR : unit terminal
    | T_THEN : unit terminal
    | T_SUB : unit terminal
    | T_STRING : (string) terminal
    | T_SIZE : unit terminal
    | T_SEMICOLON : unit terminal
    | T_R_SQ_BRK : unit terminal
    | T_R_PAR : unit terminal
    | T_R_CUR_BRK : unit terminal
    | T_RETURN : unit terminal
    | T_PRINT : unit terminal
    | T_OR : unit terminal
    | T_NULL_TYP : unit terminal
    | T_NOT : unit terminal
    | T_NEQ : unit terminal
    | T_MUL : unit terminal
    | T_MOD : unit terminal
    | T_L_SQ_BRK : unit terminal
    | T_L_PAR : unit terminal
    | T_L_CUR_BRK : unit terminal
    | T_LT : unit terminal
    | T_LEQ : unit terminal
    | T_INT_TYP : unit terminal
    | T_INT : (int) terminal
    | T_IF : unit terminal
    | T_ID : (string) terminal
    | T_GT : unit terminal
    | T_GEQ : unit terminal
    | T_FLOAT_TYP : unit terminal
    | T_FLOAT : (float) terminal
    | T_EQ : unit terminal
    | T_EOF : unit terminal
    | T_ELSE : unit terminal
    | T_DOT : unit terminal
    | T_DIV : unit terminal
    | T_DEF : unit terminal
    | T_COMMA : unit terminal
    | T_BOOL_TYP : unit terminal
    | T_BOOL : (bool) terminal
    | T_ASSIGN : unit terminal
    | T_AND : unit terminal
    | T_ADD : unit terminal
  
  (* The indexed type of nonterminal symbols. *)
  
  type _ nonterminal = 
    | N_main : (Ast.t) nonterminal
    | N_instruction : (Ast.instruction) nonterminal
    | N_function_list : (Ast.function_decl list) nonterminal
    | N_expression : (Ast.expr) nonterminal
  
  (* The inspection API. *)
  
  include MenhirLib.IncrementalEngine.INSPECTION
    with type 'a lr1state := 'a lr1state
    with type production := production
    with type 'a terminal := 'a terminal
    with type 'a nonterminal := 'a nonterminal
    with type 'a env := 'a env
  
end

(* The entry point(s) to the incremental API. *)

module Incremental : sig
  
  val main: Lexing.position -> (Ast.t) MenhirInterpreter.checkpoint
  
end
