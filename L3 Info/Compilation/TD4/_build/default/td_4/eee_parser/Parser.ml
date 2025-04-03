
(* This generated code requires the following version of MenhirLib: *)

let () =
  MenhirLib.StaticVersion.require_20240715

module MenhirBasics = struct
  
  exception Error
  
  let _eRR =
    fun _s ->
      raise Error
  
  type token = 
    | USUB
    | SUB
    | RPAR
    | REC
    | MUL
    | LPAR
    | INT of (
# 5 "td_4/eee_parser/Parser.mly"
       (int)
# 26 "td_4/eee_parser/Parser.ml"
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
          10
      | DIV ->
          9
      | EOF ->
          8
      | INT _ ->
          7
      | LPAR ->
          6
      | MUL ->
          5
      | REC ->
          4
      | RPAR ->
          3
      | SUB ->
          2
      | USUB ->
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
      | USUB ->
          Obj.repr ()
  
  and default_reduction =
    (4, "\000\t\000\007\000\000\128\004\177\n")
  
  and error =
    (11, "#\132`\140\000\003\198F\0158\000#\007\156\140\030p\000F\0158\000\000\000\000\179\128\000")
  
  and start =
    1
  
  and action =
    ((8, "NNN\000DN\005\000N\014N \000N2\000\000\000D\000"), (8, "\t\t\030\"\000\000\t*\t\017\017\030\017\000\000\017\017\017\021\021\030\021\000\000\021\021\021\005\005\030\"\000\000\005*\005\0222\030\"\000\006O*6\n\014C"))
  
  and lhs =
    (2, "*\170\148")
  
  and goto =
    ((4, "0 \004\000`\128\n\000\000\000"), (8, "\018\019\016\005\007\n\012\015"))
  
  and semantic_action =
    [|
      (fun _menhir_env ->
        let _menhir_stack = _menhir_env.MenhirLib.EngineTypes.stack in
        let {
          MenhirLib.EngineTypes.state = _;
          MenhirLib.EngineTypes.semv = expr2;
          MenhirLib.EngineTypes.startp = _startpos_expr2_;
          MenhirLib.EngineTypes.endp = _endpos_expr2_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _;
            MenhirLib.EngineTypes.semv = _2;
            MenhirLib.EngineTypes.startp = _startpos__2_;
            MenhirLib.EngineTypes.endp = _endpos__2_;
            MenhirLib.EngineTypes.next = {
              MenhirLib.EngineTypes.state = _menhir_s;
              MenhirLib.EngineTypes.semv = expr1;
              MenhirLib.EngineTypes.startp = _startpos_expr1_;
              MenhirLib.EngineTypes.endp = _endpos_expr1_;
              MenhirLib.EngineTypes.next = _menhir_stack;
            };
          };
        } = _menhir_stack in
        let expr2 : (int) = Obj.magic expr2 in
        let _2 : unit = Obj.magic _2 in
        let expr1 : (int) = Obj.magic expr1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_expr1_ in
        let _endpos = _endpos_expr2_ in
        let _v : (int) = 
# 23 "td_4/eee_parser/Parser.mly"
                            (expr1 + expr2)
# 141 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.semv = expr2;
          MenhirLib.EngineTypes.startp = _startpos_expr2_;
          MenhirLib.EngineTypes.endp = _endpos_expr2_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _;
            MenhirLib.EngineTypes.semv = _2;
            MenhirLib.EngineTypes.startp = _startpos__2_;
            MenhirLib.EngineTypes.endp = _endpos__2_;
            MenhirLib.EngineTypes.next = {
              MenhirLib.EngineTypes.state = _menhir_s;
              MenhirLib.EngineTypes.semv = expr1;
              MenhirLib.EngineTypes.startp = _startpos_expr1_;
              MenhirLib.EngineTypes.endp = _endpos_expr1_;
              MenhirLib.EngineTypes.next = _menhir_stack;
            };
          };
        } = _menhir_stack in
        let expr2 : (int) = Obj.magic expr2 in
        let _2 : unit = Obj.magic _2 in
        let expr1 : (int) = Obj.magic expr1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_expr1_ in
        let _endpos = _endpos_expr2_ in
        let _v : (int) = 
# 24 "td_4/eee_parser/Parser.mly"
                            (expr1 - expr2)
# 180 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.semv = expr;
          MenhirLib.EngineTypes.startp = _startpos_expr_;
          MenhirLib.EngineTypes.endp = _endpos_expr_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _menhir_s;
            MenhirLib.EngineTypes.semv = _1;
            MenhirLib.EngineTypes.startp = _startpos__1_;
            MenhirLib.EngineTypes.endp = _endpos__1_;
            MenhirLib.EngineTypes.next = _menhir_stack;
          };
        } = _menhir_stack in
        let expr : (int) = Obj.magic expr in
        let _1 : unit = Obj.magic _1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos__1_ in
        let _endpos = _endpos_expr_ in
        let _v : (int) = 
# 25 "td_4/eee_parser/Parser.mly"
                            (- expr)
# 212 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.semv = expr2;
          MenhirLib.EngineTypes.startp = _startpos_expr2_;
          MenhirLib.EngineTypes.endp = _endpos_expr2_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _;
            MenhirLib.EngineTypes.semv = _2;
            MenhirLib.EngineTypes.startp = _startpos__2_;
            MenhirLib.EngineTypes.endp = _endpos__2_;
            MenhirLib.EngineTypes.next = {
              MenhirLib.EngineTypes.state = _menhir_s;
              MenhirLib.EngineTypes.semv = expr1;
              MenhirLib.EngineTypes.startp = _startpos_expr1_;
              MenhirLib.EngineTypes.endp = _endpos_expr1_;
              MenhirLib.EngineTypes.next = _menhir_stack;
            };
          };
        } = _menhir_stack in
        let expr2 : (int) = Obj.magic expr2 in
        let _2 : unit = Obj.magic _2 in
        let expr1 : (int) = Obj.magic expr1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_expr1_ in
        let _endpos = _endpos_expr2_ in
        let _v : (int) = 
# 26 "td_4/eee_parser/Parser.mly"
                            (expr1 * expr2)
# 251 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.semv = expr2;
          MenhirLib.EngineTypes.startp = _startpos_expr2_;
          MenhirLib.EngineTypes.endp = _endpos_expr2_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _;
            MenhirLib.EngineTypes.semv = _2;
            MenhirLib.EngineTypes.startp = _startpos__2_;
            MenhirLib.EngineTypes.endp = _endpos__2_;
            MenhirLib.EngineTypes.next = {
              MenhirLib.EngineTypes.state = _menhir_s;
              MenhirLib.EngineTypes.semv = expr1;
              MenhirLib.EngineTypes.startp = _startpos_expr1_;
              MenhirLib.EngineTypes.endp = _endpos_expr1_;
              MenhirLib.EngineTypes.next = _menhir_stack;
            };
          };
        } = _menhir_stack in
        let expr2 : (int) = Obj.magic expr2 in
        let _2 : unit = Obj.magic _2 in
        let expr1 : (int) = Obj.magic expr1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_expr1_ in
        let _endpos = _endpos_expr2_ in
        let _v : (int) = 
# 27 "td_4/eee_parser/Parser.mly"
                            (expr1 / expr2)
# 290 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.semv = _2;
          MenhirLib.EngineTypes.startp = _startpos__2_;
          MenhirLib.EngineTypes.endp = _endpos__2_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _menhir_s;
            MenhirLib.EngineTypes.semv = expr;
            MenhirLib.EngineTypes.startp = _startpos_expr_;
            MenhirLib.EngineTypes.endp = _endpos_expr_;
            MenhirLib.EngineTypes.next = _menhir_stack;
          };
        } = _menhir_stack in
        let _2 : unit = Obj.magic _2 in
        let expr : (int) = Obj.magic expr in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_expr_ in
        let _endpos = _endpos__2_ in
        let _v : (int) = 
# 28 "td_4/eee_parser/Parser.mly"
                            (expr)
# 322 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.semv = _3;
          MenhirLib.EngineTypes.startp = _startpos__3_;
          MenhirLib.EngineTypes.endp = _endpos__3_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _;
            MenhirLib.EngineTypes.semv = expr;
            MenhirLib.EngineTypes.startp = _startpos_expr_;
            MenhirLib.EngineTypes.endp = _endpos_expr_;
            MenhirLib.EngineTypes.next = {
              MenhirLib.EngineTypes.state = _menhir_s;
              MenhirLib.EngineTypes.semv = _1;
              MenhirLib.EngineTypes.startp = _startpos__1_;
              MenhirLib.EngineTypes.endp = _endpos__1_;
              MenhirLib.EngineTypes.next = _menhir_stack;
            };
          };
        } = _menhir_stack in
        let _3 : unit = Obj.magic _3 in
        let expr : (int) = Obj.magic expr in
        let _1 : unit = Obj.magic _1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos__1_ in
        let _endpos = _endpos__3_ in
        let _v : (int) = 
# 29 "td_4/eee_parser/Parser.mly"
                            (expr)
# 361 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.state = _menhir_s;
          MenhirLib.EngineTypes.semv = expr;
          MenhirLib.EngineTypes.startp = _startpos_expr_;
          MenhirLib.EngineTypes.endp = _endpos_expr_;
          MenhirLib.EngineTypes.next = _menhir_stack;
        } = _menhir_stack in
        let expr : (
# 5 "td_4/eee_parser/Parser.mly"
       (int)
# 382 "td_4/eee_parser/Parser.ml"
        ) = Obj.magic expr in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_expr_ in
        let _endpos = _endpos_expr_ in
        let _v : (int) = 
# 30 "td_4/eee_parser/Parser.mly"
                            (expr)
# 390 "td_4/eee_parser/Parser.ml"
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
          MenhirLib.EngineTypes.semv = _2;
          MenhirLib.EngineTypes.startp = _startpos__2_;
          MenhirLib.EngineTypes.endp = _endpos__2_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _menhir_s;
            MenhirLib.EngineTypes.semv = expr;
            MenhirLib.EngineTypes.startp = _startpos_expr_;
            MenhirLib.EngineTypes.endp = _endpos_expr_;
            MenhirLib.EngineTypes.next = _menhir_stack;
          };
        } = _menhir_stack in
        let _2 : unit = Obj.magic _2 in
        let expr : (int) = Obj.magic expr in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_expr_ in
        let _endpos = _endpos__2_ in
        let _v : (unit) = 
# 19 "td_4/eee_parser/Parser.mly"
             (Format.printf "Result : %d\n"expr)
# 422 "td_4/eee_parser/Parser.ml"
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
# 20 "td_4/eee_parser/Parser.mly"
      (())
# 447 "td_4/eee_parser/Parser.ml"
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
      | T_USUB : unit terminal
      | T_SUB : unit terminal
      | T_RPAR : unit terminal
      | T_REC : unit terminal
      | T_MUL : unit terminal
      | T_LPAR : unit terminal
      | T_INT : (
# 5 "td_4/eee_parser/Parser.mly"
       (int)
# 484 "td_4/eee_parser/Parser.ml"
    ) terminal
      | T_EOF : unit terminal
      | T_DIV : unit terminal
      | T_ADD : unit terminal
    
    type _ nonterminal = 
      | N_main : (unit) nonterminal
      | N_e : (int) nonterminal
    
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
            X (T T_USUB)
        | 2 ->
            X (T T_SUB)
        | 3 ->
            X (T T_RPAR)
        | 4 ->
            X (T T_REC)
        | 5 ->
            X (T T_MUL)
        | 6 ->
            X (T T_LPAR)
        | 7 ->
            X (T T_INT)
        | 8 ->
            X (T T_EOF)
        | 9 ->
            X (T T_DIV)
        | 10 ->
            X (T T_ADD)
        | _ ->
            assert false
    
    and nonterminal =
      fun nt ->
        match nt with
        | 2 ->
            X (N N_e)
        | 1 ->
            X (N N_main)
        | _ ->
            assert false
    
    and lr0_incoming =
      (8, "\000\006\014\016\005\006\005\n\012\005\020\005\022\005\b\005\018\003\005\018")
    
    and rhs =
      ((8, "\003\005\022\005\005\006\005\006\005\005\012\005\005\020\005\005\n\014\005\b\016\005\018\018"), (8, "\000\001\004\007\t\012\015\017\020\021\023\024"))
    
    and lr0_core =
      (8, "\000\001\002\003\004\005\006\007\b\t\n\011\014\012\r\015\016\017\018\019")
    
    and lr0_items =
      ((16, "\000\000\012\001\028\001 \001\028\002\024\001\020\001\016\001\b\001\004\001\b\002\024\001\020\001\016\001\b\003\b\001\004\001\024\002\016\002\024\001\020\001\016\003\016\001\b\001\004\001\020\002\024\001\020\003\020\001\016\001\b\001\004\001\004\002\024\001\020\001\016\001\b\001\004\003\004\001\028\003\024\001\020\001\016\001\012\002\b\001\004\001(\001\000\001$\001\024\001\020\001\016\001\b\001\004\001$\002"), (8, "\000\001\002\003\004\n\011\017\018\019\025\026 !'(./067"))
    
    and nullable =
      "\000"
    
    and first =
      (11, "#\132p\140\000")
    
  end) (ET) (TI)
  
end

let main =
  fun lexer lexbuf : (unit) ->
    Obj.magic (MenhirInterpreter.entry `Legacy 0 lexer lexbuf)

module Incremental = struct
  
  let main =
    fun initial_position : (unit) MenhirInterpreter.checkpoint ->
      Obj.magic (MenhirInterpreter.start 0 initial_position)
  
end
