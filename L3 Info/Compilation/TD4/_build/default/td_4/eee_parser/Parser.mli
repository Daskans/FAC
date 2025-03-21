
(* The type of tokens. *)

type token = 
  | SUB
  | RPAR
  | REC
  | MUL
  | LPAR
  | INT of (int)
  | EOF
  | DIV
  | ADD

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val main: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (unit)

module MenhirInterpreter : sig
  
  (* The incremental API. *)
  
  include MenhirLib.IncrementalEngine.INCREMENTAL_ENGINE
    with type token = token
  
  (* The indexed type of terminal symbols. *)
  
  type _ terminal = 
    | T_error : unit terminal
    | T_SUB : unit terminal
    | T_RPAR : unit terminal
    | T_REC : unit terminal
    | T_MUL : unit terminal
    | T_LPAR : unit terminal
    | T_INT : (int) terminal
    | T_EOF : unit terminal
    | T_DIV : unit terminal
    | T_ADD : unit terminal
  
  (* The indexed type of nonterminal symbols. *)
  
  type _ nonterminal = 
    | N_s : (unit) nonterminal
    | N_main : (unit) nonterminal
  
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
  
  val main: Lexing.position -> (unit) MenhirInterpreter.checkpoint
  
end
