
(* This generated code requires the following version of MenhirLib: *)

let () =
  MenhirLib.StaticVersion.require_20230608

module MenhirBasics = struct
  
  exception Error
  
  let _eRR =
    fun _s ->
      raise Error
  
  type token = 
    | SUB
    | RPAR
    | REC
    | MUL
    | LPAR
    | INT of (
# 4 "td_4/etf_parser/Parser.mly"
       (int)
# 25 "td_4/etf_parser/Parser.ml"
  )
    | EOF
    | DIV
    | ADD
  
end

include MenhirBasics

module Tables = struct
  
  include MenhirBasics
  
  let token2terminal : token -> int =
    fun _tok ->
      match _tok with
      | ADD ->
          9
      | DIV ->
          8
      | EOF ->
          7
      | INT _ ->
          6
      | LPAR ->
          5
      | MUL ->
          4
      | REC ->
          3
      | RPAR ->
          2
      | SUB ->
          1
  
  and error_terminal =
    0
  
  and token2value : token -> Obj.t =
    fun _tok ->
      match _tok with
      | ADD ->
          Obj.repr ()
      | DIV ->
          Obj.repr ()
      | EOF ->
          Obj.repr ()
      | INT _v ->
          Obj.repr _v
      | LPAR ->
          Obj.repr ()
      | MUL ->
          Obj.repr ()
      | REC ->
          Obj.repr ()
      | RPAR ->
          Obj.repr ()
      | SUB ->
          Obj.repr ()
  
  and default_reduction =
    (2, " \000\r")
  
  and error =
    (10, "\001@\004\000 \000\132\000@\128\002\000@\000\000")
  
  and start =
    1
  
  and action =
    ((4, "\240\003\148*D\000"), (8, "\007\014\n\018\022\026\030\"&+"))
  
  and lhs =
    (1, "`")
  
  and goto =
    ((2, "\192\000\000"), (4, "\192"))
  
  and semantic_action =
    [|
      (fun _menhir_env ->
        let _menhir_stack = _menhir_env.MenhirLib.EngineTypes.stack in
        let {
          MenhirLib.EngineTypes.state = _menhir_s;
          MenhirLib.EngineTypes.semv = _1;
          MenhirLib.EngineTypes.startp = _startpos__1_;
          MenhirLib.EngineTypes.endp = _endpos__1_;
          MenhirLib.EngineTypes.next = _menhir_stack;
        } = _menhir_stack in
        let _1 : unit = Obj.magic _1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos__1_ in
        let _endpos = _endpos__1_ in
        let _v : (unit) = 
# 12 "td_4/etf_parser/Parser.mly"
              ()
# 122 "td_4/etf_parser/Parser.ml"
         in
        {
          MenhirLib.EngineTypes.state = _menhir_s;
          MenhirLib.EngineTypes.semv = Obj.repr _v;
          MenhirLib.EngineTypes.startp = _startpos;
          MenhirLib.EngineTypes.endp = _endpos;
          MenhirLib.EngineTypes.next = _menhir_stack;
        });
      (fun _menhir_env ->
        let _menhir_stack = _menhir_env.MenhirLib.EngineTypes.stack in
        let {
          MenhirLib.EngineTypes.state = _;
          MenhirLib.EngineTypes.semv = _9;
          MenhirLib.EngineTypes.startp = _startpos__9_;
          MenhirLib.EngineTypes.endp = _endpos__9_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _;
            MenhirLib.EngineTypes.semv = _8;
            MenhirLib.EngineTypes.startp = _startpos__8_;
            MenhirLib.EngineTypes.endp = _endpos__8_;
            MenhirLib.EngineTypes.next = {
              MenhirLib.EngineTypes.state = _;
              MenhirLib.EngineTypes.semv = _7;
              MenhirLib.EngineTypes.startp = _startpos__7_;
              MenhirLib.EngineTypes.endp = _endpos__7_;
              MenhirLib.EngineTypes.next = {
                MenhirLib.EngineTypes.state = _;
                MenhirLib.EngineTypes.semv = _6;
                MenhirLib.EngineTypes.startp = _startpos__6_;
                MenhirLib.EngineTypes.endp = _endpos__6_;
                MenhirLib.EngineTypes.next = {
                  MenhirLib.EngineTypes.state = _;
                  MenhirLib.EngineTypes.semv = _5;
                  MenhirLib.EngineTypes.startp = _startpos__5_;
                  MenhirLib.EngineTypes.endp = _endpos__5_;
                  MenhirLib.EngineTypes.next = {
                    MenhirLib.EngineTypes.state = _;
                    MenhirLib.EngineTypes.semv = _4;
                    MenhirLib.EngineTypes.startp = _startpos__4_;
                    MenhirLib.EngineTypes.endp = _endpos__4_;
                    MenhirLib.EngineTypes.next = {
                      MenhirLib.EngineTypes.state = _;
                      MenhirLib.EngineTypes.semv = _3;
                      MenhirLib.EngineTypes.startp = _startpos__3_;
                      MenhirLib.EngineTypes.endp = _endpos__3_;
                      MenhirLib.EngineTypes.next = {
                        MenhirLib.EngineTypes.state = _;
                        MenhirLib.EngineTypes.semv = _2;
                        MenhirLib.EngineTypes.startp = _startpos__2_;
                        MenhirLib.EngineTypes.endp = _endpos__2_;
                        MenhirLib.EngineTypes.next = {
                          MenhirLib.EngineTypes.state = _menhir_s;
                          MenhirLib.EngineTypes.semv = _1;
                          MenhirLib.EngineTypes.startp = _startpos__1_;
                          MenhirLib.EngineTypes.endp = _endpos__1_;
                          MenhirLib.EngineTypes.next = _menhir_stack;
                        };
                      };
                    };
                  };
                };
              };
            };
          };
        } = _menhir_stack in
        let _9 : unit = Obj.magic _9 in
        let _8 : (
# 4 "td_4/etf_parser/Parser.mly"
       (int)
# 192 "td_4/etf_parser/Parser.ml"
        ) = Obj.magic _8 in
        let _7 : unit = Obj.magic _7 in
        let _6 : unit = Obj.magic _6 in
        let _5 : unit = Obj.magic _5 in
        let _4 : unit = Obj.magic _4 in
        let _3 : unit = Obj.magic _3 in
        let _2 : unit = Obj.magic _2 in
        let _1 : unit = Obj.magic _1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos__1_ in
        let _endpos = _endpos__9_ in
        let _v : (unit) = 
# 13 "td_4/etf_parser/Parser.mly"
                                        ( (* À enlever -- ici pour éviter des warnings !*))
# 207 "td_4/etf_parser/Parser.ml"
         in
        {
          MenhirLib.EngineTypes.state = _menhir_s;
          MenhirLib.EngineTypes.semv = Obj.repr _v;
          MenhirLib.EngineTypes.startp = _startpos;
          MenhirLib.EngineTypes.endp = _endpos;
          MenhirLib.EngineTypes.next = _menhir_stack;
        });
    |]
  
  and trace =
    None
  
end

module MenhirInterpreter = struct
  
  module ET = MenhirLib.TableInterpreter.MakeEngineTable (Tables)
  
  module TI = MenhirLib.Engine.Make (ET)
  
  include TI
  
  module Symbols = struct
    
    type _ terminal = 
      | T_error : unit terminal
      | T_SUB : unit terminal
      | T_RPAR : unit terminal
      | T_REC : unit terminal
      | T_MUL : unit terminal
      | T_LPAR : unit terminal
      | T_INT : (
# 4 "td_4/etf_parser/Parser.mly"
       (int)
# 243 "td_4/etf_parser/Parser.ml"
    ) terminal
      | T_EOF : unit terminal
      | T_DIV : unit terminal
      | T_ADD : unit terminal
    
    type _ nonterminal = 
      | N_main : (unit) nonterminal
    
  end
  
  include Symbols
  
  include MenhirLib.InspectionTableInterpreter.Make (Tables) (struct
    
    include TI
    
    include Symbols
    
    include MenhirLib.InspectionTableInterpreter.Symbols (Symbols)
    
    let terminal =
      fun t ->
        match t with
        | 0 ->
            X (T T_error)
        | 1 ->
            X (T T_SUB)
        | 2 ->
            X (T T_RPAR)
        | 3 ->
            X (T T_REC)
        | 4 ->
            X (T T_MUL)
        | 5 ->
            X (T T_LPAR)
        | 6 ->
            X (T T_INT)
        | 7 ->
            X (T T_EOF)
        | 8 ->
            X (T T_DIV)
        | 9 ->
            X (T T_ADD)
        | _ ->
            assert false
    
    and nonterminal =
      fun nt ->
        match nt with
        | 1 ->
            X (N N_main)
        | _ ->
            assert false
    
    and lr0_incoming =
      (8, "\000\016\020\004\n\018\b\012\006\014\016\003")
    
    and rhs =
      ((8, "\003\016\020\004\n\018\b\012\006\014\016"), (4, "\001+"))
    
    and lr0_core =
      (4, "\001#Eg\137\171")
    
    and lr0_items =
      ((16, "\000\000\004\001\b\001\b\002\b\003\b\004\b\005\b\006\b\007\b\b\b\t\000\001"), (4, "\001#Eg\137\171\192"))
    
    and nullable =
      "\000"
    
    and first =
      (10, "\001@P")
    
  end) (ET) (TI)
  
end

let main =
  fun lexer lexbuf ->
    (Obj.magic (MenhirInterpreter.entry `Legacy 0 lexer lexbuf) : (unit))

module Incremental = struct
  
  let main =
    fun initial_position ->
      (Obj.magic (MenhirInterpreter.start 0 initial_position) : (unit) MenhirInterpreter.checkpoint)
  
end
