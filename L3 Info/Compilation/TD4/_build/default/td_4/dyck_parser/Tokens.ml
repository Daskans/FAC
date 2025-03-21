
type token = 
  | EOF
  | B
  | A

module MenhirInterpreter = struct
  
  type _ terminal = 
    | T_error : unit terminal
    | T_EOF : unit terminal
    | T_B : unit terminal
    | T_A : unit terminal
  
end
