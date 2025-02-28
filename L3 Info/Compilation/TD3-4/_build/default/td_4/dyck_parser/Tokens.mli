
(* The type of tokens. *)

type token = 
  | EOF
  | B
  | A

module MenhirInterpreter : sig
  
  (* The indexed type of terminal symbols. *)
  
  type _ terminal = 
    | T_error : unit terminal
    | T_EOF : unit terminal
    | T_B : unit terminal
    | T_A : unit terminal
  
end
