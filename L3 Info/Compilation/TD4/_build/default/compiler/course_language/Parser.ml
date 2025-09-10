
(* This generated code requires the following version of MenhirLib: *)

let () =
  MenhirLib.StaticVersion.require_20240715

module MenhirBasics = struct
  
  exception Error
  
  let _eRR =
    fun _s ->
      raise Error
  
  type token = 
    | WHILE
    | VAR
    | THEN
    | SUB
    | STRING of (
# 43 "compiler/course_language/Parser.mly"
       (string)
# 24 "compiler/course_language/Parser.ml"
  )
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
    | INT of (
# 44 "compiler/course_language/Parser.mly"
       (int)
# 48 "compiler/course_language/Parser.ml"
  )
    | IF
    | ID of (
# 42 "compiler/course_language/Parser.mly"
       (string)
# 54 "compiler/course_language/Parser.ml"
  )
    | GT
    | GEQ
    | FLOAT_TYP
    | FLOAT of (
# 45 "compiler/course_language/Parser.mly"
       (float)
# 62 "compiler/course_language/Parser.ml"
  )
    | EQ
    | EOF
    | ELSE
    | DOT
    | DIV
    | DEF
    | COMMA
    | BOOL_TYP
    | BOOL of (
# 46 "compiler/course_language/Parser.mly"
       (bool)
# 75 "compiler/course_language/Parser.ml"
  )
    | ASSIGN
    | AND
    | ADD
  
end

include MenhirBasics

# 1 "compiler/course_language/Parser.mly"
  
    open Ast

# 89 "compiler/course_language/Parser.ml"

module Tables = struct
  
  include MenhirBasics
  
  let token2terminal : token -> int =
    fun _tok ->
      match _tok with
      | ADD ->
          43
      | AND ->
          42
      | ASSIGN ->
          41
      | BOOL _ ->
          40
      | BOOL_TYP ->
          39
      | COMMA ->
          38
      | DEF ->
          37
      | DIV ->
          36
      | DOT ->
          35
      | ELSE ->
          34
      | EOF ->
          33
      | EQ ->
          32
      | FLOAT _ ->
          31
      | FLOAT_TYP ->
          30
      | GEQ ->
          29
      | GT ->
          28
      | ID _ ->
          27
      | IF ->
          26
      | INT _ ->
          25
      | INT_TYP ->
          24
      | LEQ ->
          23
      | LT ->
          22
      | L_CUR_BRK ->
          21
      | L_PAR ->
          20
      | L_SQ_BRK ->
          19
      | MOD ->
          18
      | MUL ->
          17
      | NEQ ->
          16
      | NOT ->
          15
      | NULL_TYP ->
          14
      | OR ->
          13
      | PRINT ->
          12
      | RETURN ->
          11
      | R_CUR_BRK ->
          10
      | R_PAR ->
          9
      | R_SQ_BRK ->
          8
      | SEMICOLON ->
          7
      | SIZE ->
          6
      | STRING _ ->
          5
      | SUB ->
          4
      | THEN ->
          3
      | VAR ->
          2
      | WHILE ->
          1
  
  and error_terminal =
    0
  
  and token2value : token -> Obj.t =
    fun _tok ->
      match _tok with
      | ADD ->
          Obj.repr ()
      | AND ->
          Obj.repr ()
      | ASSIGN ->
          Obj.repr ()
      | BOOL _v ->
          Obj.repr _v
      | BOOL_TYP ->
          Obj.repr ()
      | COMMA ->
          Obj.repr ()
      | DEF ->
          Obj.repr ()
      | DIV ->
          Obj.repr ()
      | DOT ->
          Obj.repr ()
      | ELSE ->
          Obj.repr ()
      | EOF ->
          Obj.repr ()
      | EQ ->
          Obj.repr ()
      | FLOAT _v ->
          Obj.repr _v
      | FLOAT_TYP ->
          Obj.repr ()
      | GEQ ->
          Obj.repr ()
      | GT ->
          Obj.repr ()
      | ID _v ->
          Obj.repr _v
      | IF ->
          Obj.repr ()
      | INT _v ->
          Obj.repr _v
      | INT_TYP ->
          Obj.repr ()
      | LEQ ->
          Obj.repr ()
      | LT ->
          Obj.repr ()
      | L_CUR_BRK ->
          Obj.repr ()
      | L_PAR ->
          Obj.repr ()
      | L_SQ_BRK ->
          Obj.repr ()
      | MOD ->
          Obj.repr ()
      | MUL ->
          Obj.repr ()
      | NEQ ->
          Obj.repr ()
      | NOT ->
          Obj.repr ()
      | NULL_TYP ->
          Obj.repr ()
      | OR ->
          Obj.repr ()
      | PRINT ->
          Obj.repr ()
      | RETURN ->
          Obj.repr ()
      | R_CUR_BRK ->
          Obj.repr ()
      | R_PAR ->
          Obj.repr ()
      | R_SQ_BRK ->
          Obj.repr ()
      | SEMICOLON ->
          Obj.repr ()
      | SIZE ->
          Obj.repr ()
      | STRING _v ->
          Obj.repr _v
      | SUB ->
          Obj.repr ()
      | THEN ->
          Obj.repr ()
      | VAR ->
          Obj.repr ()
      | WHILE ->
          Obj.repr ()
  
  and default_reduction =
    (4, "\005 \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\004\016p`\128")
  
  and error =
    (44, "\001\000\000`@\000\000\000\000\000\000\000\000\000\000\000\001\000\000\000\000\000\000\000\000\000 \004\000\000\000\000\000\000\000\b\000\000\000\004\000\000\000\000\000\000\004\000\000\000\002\000\000\000\000\000\000\016\000\000\000\b\000\000\000\000\000\000\000\000\000\016\128\000\000\000\000\000\000@\000\000\000\000\000\000\000\128\000\000 \000\000\000\000\000\000\000\002\000\004\000\000\000\000\000\016\000\000\000\000\000\000\000\128\000\000\b\000\000\000\000\000\002\000\000\000\000\000\000\128\000\000\000\001\000\000\000\000\000\000@\000\000\000\000\000\002\000\016\000\000\000\000\000\000\000\000\000@\000\000\000\000@\000\000\000\000\016\000\000\128\000\000\000\002\000\000\000\000\000\001\000\000\000\000\000\000\000\128\000\000\000\000\000 \000\000\000\000\000\001\000\000 \000\000\000 \000\000\000\000\000\000\000\001\000\000\004\000\000\000\000\000\000\000\004\000\000\000\000\000\001\000\000\000\000\000\000\b\000\000\000\000@\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\004\000\000\000\000\000\000\000\000\000\000\004\000\000\000\000\000\000\000\000\000\000\004\000\000\000\000\000\000\000")
  
  and start =
    1
  
  and action =
    ((8, "\015\000\000\005A\004!\t\031\007\023\002C\014\011/\t7\006\004\025\n\000\011\002\t\023*\025\015\t(6.\022\012\0050J\026H\"\024\b\024\000\000\026\000\028\000\030\000"), (8, "\006\018\022\026\030\"&*.26:>BFJNR\n\014VZ^bfj\tnrvz~\130\134\138\142\146\150\154\158\162\166\170\174\178\182\195\203\211"))
  
  and lhs =
    (4, "\0043!\017")
  
  and goto =
    ((2, "\192\000\000\000\000\000\000\000\000\000\000\000\000\000"), (8, "/024"))
  
  and semantic_action =
    [|
      (fun _menhir_env ->
        let _menhir_stack = _menhir_env.MenhirLib.EngineTypes.stack in
        let {
          MenhirLib.EngineTypes.state = _menhir_s;
          MenhirLib.EngineTypes.semv = i;
          MenhirLib.EngineTypes.startp = _startpos_i_;
          MenhirLib.EngineTypes.endp = _endpos_i_;
          MenhirLib.EngineTypes.next = _menhir_stack;
        } = _menhir_stack in
        let i : (
# 44 "compiler/course_language/Parser.mly"
       (int)
# 310 "compiler/course_language/Parser.ml"
        ) = Obj.magic i in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_i_ in
        let _endpos = _endpos_i_ in
        let _v =
          let _endpos = _endpos_i_ in
          let _startpos = _startpos_i_ in
          let _loc = (_startpos, _endpos) in
          (
# 66 "compiler/course_language/Parser.mly"
          ( Cst_i (i,Annotation.create _loc) )
# 322 "compiler/course_language/Parser.ml"
           : (Ast.expr))
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
        let _menhir_s = _menhir_env.MenhirLib.EngineTypes.current in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _endpos = _startpos in
        let _v : (Ast.function_decl list) = 
# 59 "compiler/course_language/Parser.mly"
   ([])
# 341 "compiler/course_language/Parser.ml"
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
          MenhirLib.EngineTypes.semv = _43;
          MenhirLib.EngineTypes.startp = _startpos__43_;
          MenhirLib.EngineTypes.endp = _endpos__43_;
          MenhirLib.EngineTypes.next = {
            MenhirLib.EngineTypes.state = _;
            MenhirLib.EngineTypes.semv = _42;
            MenhirLib.EngineTypes.startp = _startpos__42_;
            MenhirLib.EngineTypes.endp = _endpos__42_;
            MenhirLib.EngineTypes.next = {
              MenhirLib.EngineTypes.state = _;
              MenhirLib.EngineTypes.semv = _41;
              MenhirLib.EngineTypes.startp = _startpos__41_;
              MenhirLib.EngineTypes.endp = _endpos__41_;
              MenhirLib.EngineTypes.next = {
                MenhirLib.EngineTypes.state = _;
                MenhirLib.EngineTypes.semv = _40;
                MenhirLib.EngineTypes.startp = _startpos__40_;
                MenhirLib.EngineTypes.endp = _endpos__40_;
                MenhirLib.EngineTypes.next = {
                  MenhirLib.EngineTypes.state = _;
                  MenhirLib.EngineTypes.semv = _39;
                  MenhirLib.EngineTypes.startp = _startpos__39_;
                  MenhirLib.EngineTypes.endp = _endpos__39_;
                  MenhirLib.EngineTypes.next = {
                    MenhirLib.EngineTypes.state = _;
                    MenhirLib.EngineTypes.semv = _38;
                    MenhirLib.EngineTypes.startp = _startpos__38_;
                    MenhirLib.EngineTypes.endp = _endpos__38_;
                    MenhirLib.EngineTypes.next = {
                      MenhirLib.EngineTypes.state = _;
                      MenhirLib.EngineTypes.semv = _37;
                      MenhirLib.EngineTypes.startp = _startpos__37_;
                      MenhirLib.EngineTypes.endp = _endpos__37_;
                      MenhirLib.EngineTypes.next = {
                        MenhirLib.EngineTypes.state = _;
                        MenhirLib.EngineTypes.semv = _36;
                        MenhirLib.EngineTypes.startp = _startpos__36_;
                        MenhirLib.EngineTypes.endp = _endpos__36_;
                        MenhirLib.EngineTypes.next = {
                          MenhirLib.EngineTypes.state = _;
                          MenhirLib.EngineTypes.semv = _35;
                          MenhirLib.EngineTypes.startp = _startpos__35_;
                          MenhirLib.EngineTypes.endp = _endpos__35_;
                          MenhirLib.EngineTypes.next = {
                            MenhirLib.EngineTypes.state = _;
                            MenhirLib.EngineTypes.semv = _34;
                            MenhirLib.EngineTypes.startp = _startpos__34_;
                            MenhirLib.EngineTypes.endp = _endpos__34_;
                            MenhirLib.EngineTypes.next = {
                              MenhirLib.EngineTypes.state = _;
                              MenhirLib.EngineTypes.semv = _33;
                              MenhirLib.EngineTypes.startp = _startpos__33_;
                              MenhirLib.EngineTypes.endp = _endpos__33_;
                              MenhirLib.EngineTypes.next = {
                                MenhirLib.EngineTypes.state = _;
                                MenhirLib.EngineTypes.semv = _32;
                                MenhirLib.EngineTypes.startp = _startpos__32_;
                                MenhirLib.EngineTypes.endp = _endpos__32_;
                                MenhirLib.EngineTypes.next = {
                                  MenhirLib.EngineTypes.state = _;
                                  MenhirLib.EngineTypes.semv = _31;
                                  MenhirLib.EngineTypes.startp = _startpos__31_;
                                  MenhirLib.EngineTypes.endp = _endpos__31_;
                                  MenhirLib.EngineTypes.next = {
                                    MenhirLib.EngineTypes.state = _;
                                    MenhirLib.EngineTypes.semv = _30;
                                    MenhirLib.EngineTypes.startp = _startpos__30_;
                                    MenhirLib.EngineTypes.endp = _endpos__30_;
                                    MenhirLib.EngineTypes.next = {
                                      MenhirLib.EngineTypes.state = _;
                                      MenhirLib.EngineTypes.semv = _29;
                                      MenhirLib.EngineTypes.startp = _startpos__29_;
                                      MenhirLib.EngineTypes.endp = _endpos__29_;
                                      MenhirLib.EngineTypes.next = {
                                        MenhirLib.EngineTypes.state = _;
                                        MenhirLib.EngineTypes.semv = _28;
                                        MenhirLib.EngineTypes.startp = _startpos__28_;
                                        MenhirLib.EngineTypes.endp = _endpos__28_;
                                        MenhirLib.EngineTypes.next = {
                                          MenhirLib.EngineTypes.state = _;
                                          MenhirLib.EngineTypes.semv = _27;
                                          MenhirLib.EngineTypes.startp = _startpos__27_;
                                          MenhirLib.EngineTypes.endp = _endpos__27_;
                                          MenhirLib.EngineTypes.next = {
                                            MenhirLib.EngineTypes.state = _;
                                            MenhirLib.EngineTypes.semv = _26;
                                            MenhirLib.EngineTypes.startp = _startpos__26_;
                                            MenhirLib.EngineTypes.endp = _endpos__26_;
                                            MenhirLib.EngineTypes.next = {
                                              MenhirLib.EngineTypes.state = _;
                                              MenhirLib.EngineTypes.semv = _25;
                                              MenhirLib.EngineTypes.startp = _startpos__25_;
                                              MenhirLib.EngineTypes.endp = _endpos__25_;
                                              MenhirLib.EngineTypes.next = {
                                                MenhirLib.EngineTypes.state = _;
                                                MenhirLib.EngineTypes.semv = _24;
                                                MenhirLib.EngineTypes.startp = _startpos__24_;
                                                MenhirLib.EngineTypes.endp = _endpos__24_;
                                                MenhirLib.EngineTypes.next = {
                                                  MenhirLib.EngineTypes.state = _;
                                                  MenhirLib.EngineTypes.semv = _23;
                                                  MenhirLib.EngineTypes.startp = _startpos__23_;
                                                  MenhirLib.EngineTypes.endp = _endpos__23_;
                                                  MenhirLib.EngineTypes.next = {
                                                    MenhirLib.EngineTypes.state = _;
                                                    MenhirLib.EngineTypes.semv = _22;
                                                    MenhirLib.EngineTypes.startp = _startpos__22_;
                                                    MenhirLib.EngineTypes.endp = _endpos__22_;
                                                    MenhirLib.EngineTypes.next = {
                                                      MenhirLib.EngineTypes.state = _;
                                                      MenhirLib.EngineTypes.semv = _21;
                                                      MenhirLib.EngineTypes.startp = _startpos__21_;
                                                      MenhirLib.EngineTypes.endp = _endpos__21_;
                                                      MenhirLib.EngineTypes.next = {
                                                        MenhirLib.EngineTypes.state = _;
                                                        MenhirLib.EngineTypes.semv = _20;
                                                        MenhirLib.EngineTypes.startp = _startpos__20_;
                                                        MenhirLib.EngineTypes.endp = _endpos__20_;
                                                        MenhirLib.EngineTypes.next = {
                                                          MenhirLib.EngineTypes.state = _;
                                                          MenhirLib.EngineTypes.semv = _19;
                                                          MenhirLib.EngineTypes.startp = _startpos__19_;
                                                          MenhirLib.EngineTypes.endp = _endpos__19_;
                                                          MenhirLib.EngineTypes.next = {
                                                            MenhirLib.EngineTypes.state = _;
                                                            MenhirLib.EngineTypes.semv = _18;
                                                            MenhirLib.EngineTypes.startp = _startpos__18_;
                                                            MenhirLib.EngineTypes.endp = _endpos__18_;
                                                            MenhirLib.EngineTypes.next = {
                                                              MenhirLib.EngineTypes.state = _;
                                                              MenhirLib.EngineTypes.semv = _17;
                                                              MenhirLib.EngineTypes.startp = _startpos__17_;
                                                              MenhirLib.EngineTypes.endp = _endpos__17_;
                                                              MenhirLib.EngineTypes.next = {
                                                                MenhirLib.EngineTypes.state = _;
                                                                MenhirLib.EngineTypes.semv = _16;
                                                                MenhirLib.EngineTypes.startp = _startpos__16_;
                                                                MenhirLib.EngineTypes.endp = _endpos__16_;
                                                                MenhirLib.EngineTypes.next = {
                                                                  MenhirLib.EngineTypes.state = _;
                                                                  MenhirLib.EngineTypes.semv = _15;
                                                                  MenhirLib.EngineTypes.startp = _startpos__15_;
                                                                  MenhirLib.EngineTypes.endp = _endpos__15_;
                                                                  MenhirLib.EngineTypes.next = {
                                                                    MenhirLib.EngineTypes.state = _;
                                                                    MenhirLib.EngineTypes.semv = _14;
                                                                    MenhirLib.EngineTypes.startp = _startpos__14_;
                                                                    MenhirLib.EngineTypes.endp = _endpos__14_;
                                                                    MenhirLib.EngineTypes.next = {
                                                                      MenhirLib.EngineTypes.state = _;
                                                                      MenhirLib.EngineTypes.semv = _13;
                                                                      MenhirLib.EngineTypes.startp = _startpos__13_;
                                                                      MenhirLib.EngineTypes.endp = _endpos__13_;
                                                                      MenhirLib.EngineTypes.next = {
                                                                        MenhirLib.EngineTypes.state = _;
                                                                        MenhirLib.EngineTypes.semv = _12;
                                                                        MenhirLib.EngineTypes.startp = _startpos__12_;
                                                                        MenhirLib.EngineTypes.endp = _endpos__12_;
                                                                        MenhirLib.EngineTypes.next = {
                                                                          MenhirLib.EngineTypes.state = _;
                                                                          MenhirLib.EngineTypes.semv = _11;
                                                                          MenhirLib.EngineTypes.startp = _startpos__11_;
                                                                          MenhirLib.EngineTypes.endp = _endpos__11_;
                                                                          MenhirLib.EngineTypes.next = {
                                                                            MenhirLib.EngineTypes.state = _;
                                                                            MenhirLib.EngineTypes.semv = _10;
                                                                            MenhirLib.EngineTypes.startp = _startpos__10_;
                                                                            MenhirLib.EngineTypes.endp = _endpos__10_;
                                                                            MenhirLib.EngineTypes.next = {
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
                                                                            };
                                                                          };
                                                                        };
                                                                      };
                                                                    };
                                                                  };
                                                                };
                                                              };
                                                            };
                                                          };
                                                        };
                                                      };
                                                    };
                                                  };
                                                };
                                              };
                                            };
                                          };
                                        };
                                      };
                                    };
                                  };
                                };
                              };
                            };
                          };
                        };
                      };
                    };
                  };
                };
              };
            };
          };
        } = _menhir_stack in
        let _43 : unit = Obj.magic _43 in
        let _42 : (
# 46 "compiler/course_language/Parser.mly"
       (bool)
# 615 "compiler/course_language/Parser.ml"
        ) = Obj.magic _42 in
        let _41 : (
# 45 "compiler/course_language/Parser.mly"
       (float)
# 620 "compiler/course_language/Parser.ml"
        ) = Obj.magic _41 in
        let _40 : (
# 44 "compiler/course_language/Parser.mly"
       (int)
# 625 "compiler/course_language/Parser.ml"
        ) = Obj.magic _40 in
        let _39 : (
# 43 "compiler/course_language/Parser.mly"
       (string)
# 630 "compiler/course_language/Parser.ml"
        ) = Obj.magic _39 in
        let _38 : (
# 42 "compiler/course_language/Parser.mly"
       (string)
# 635 "compiler/course_language/Parser.ml"
        ) = Obj.magic _38 in
        let _37 : unit = Obj.magic _37 in
        let _36 : unit = Obj.magic _36 in
        let _35 : unit = Obj.magic _35 in
        let _34 : unit = Obj.magic _34 in
        let _33 : unit = Obj.magic _33 in
        let _32 : unit = Obj.magic _32 in
        let _31 : unit = Obj.magic _31 in
        let _30 : unit = Obj.magic _30 in
        let _29 : unit = Obj.magic _29 in
        let _28 : unit = Obj.magic _28 in
        let _27 : unit = Obj.magic _27 in
        let _26 : unit = Obj.magic _26 in
        let _25 : unit = Obj.magic _25 in
        let _24 : unit = Obj.magic _24 in
        let _23 : unit = Obj.magic _23 in
        let _22 : unit = Obj.magic _22 in
        let _21 : unit = Obj.magic _21 in
        let _20 : unit = Obj.magic _20 in
        let _19 : unit = Obj.magic _19 in
        let _18 : unit = Obj.magic _18 in
        let _17 : unit = Obj.magic _17 in
        let _16 : unit = Obj.magic _16 in
        let _15 : unit = Obj.magic _15 in
        let _14 : unit = Obj.magic _14 in
        let _13 : unit = Obj.magic _13 in
        let _12 : unit = Obj.magic _12 in
        let _11 : unit = Obj.magic _11 in
        let _10 : unit = Obj.magic _10 in
        let _9 : unit = Obj.magic _9 in
        let _8 : unit = Obj.magic _8 in
        let _7 : unit = Obj.magic _7 in
        let _6 : unit = Obj.magic _6 in
        let _5 : unit = Obj.magic _5 in
        let _4 : unit = Obj.magic _4 in
        let _3 : unit = Obj.magic _3 in
        let _2 : unit = Obj.magic _2 in
        let _1 : unit = Obj.magic _1 in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos__1_ in
        let _endpos = _endpos__43_ in
        let _v : (Ast.function_decl list) = 
# 60 "compiler/course_language/Parser.mly"
                                                                                                                                                                                                                                                 ( (*À retirer -- ici pour éviter les warnings avant de commencer*) [])
# 680 "compiler/course_language/Parser.ml"
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
        let _v =
          let _endpos = _endpos__1_ in
          let _startpos = _startpos__1_ in
          let _loc = (_startpos, _endpos) in
          (
# 63 "compiler/course_language/Parser.mly"
            (Block ([],Annotation.create _loc) )
# 709 "compiler/course_language/Parser.ml"
           : (Ast.instruction))
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
            MenhirLib.EngineTypes.semv = l;
            MenhirLib.EngineTypes.startp = _startpos_l_;
            MenhirLib.EngineTypes.endp = _endpos_l_;
            MenhirLib.EngineTypes.next = _menhir_stack;
          };
        } = _menhir_stack in
        let _2 : unit = Obj.magic _2 in
        let l : (Ast.function_decl list) = Obj.magic l in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_l_ in
        let _endpos = _endpos__2_ in
        let _v : (Ast.t) = 
# 54 "compiler/course_language/Parser.mly"
                        ( Program (List.rev l) (*Le List.rev est là si vous construisez la liste à l’envers (ce qui arrive si vous le faites avec une associativité à gauche (si vous voulez que l’arbre reste petit)). Si vous la construisez dans le bon sens, retirez le List.rev.*))
# 742 "compiler/course_language/Parser.ml"
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
            MenhirLib.EngineTypes.semv = i;
            MenhirLib.EngineTypes.startp = _startpos_i_;
            MenhirLib.EngineTypes.endp = _endpos_i_;
            MenhirLib.EngineTypes.next = _menhir_stack;
          };
        } = _menhir_stack in
        let _2 : unit = Obj.magic _2 in
        let i : (Ast.instruction) = Obj.magic i in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_i_ in
        let _endpos = _endpos__2_ in
        let _v : (Ast.t) = 
# 55 "compiler/course_language/Parser.mly"
                      ( Instruction i )
# 774 "compiler/course_language/Parser.ml"
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
            MenhirLib.EngineTypes.semv = e;
            MenhirLib.EngineTypes.startp = _startpos_e_;
            MenhirLib.EngineTypes.endp = _endpos_e_;
            MenhirLib.EngineTypes.next = _menhir_stack;
          };
        } = _menhir_stack in
        let _2 : unit = Obj.magic _2 in
        let e : (Ast.expr) = Obj.magic e in
        let _endpos__0_ = _menhir_stack.MenhirLib.EngineTypes.endp in
        let _startpos = _startpos_e_ in
        let _endpos = _endpos__2_ in
        let _v : (Ast.t) = 
# 56 "compiler/course_language/Parser.mly"
                     ( Expression e )
# 806 "compiler/course_language/Parser.ml"
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
      | T_WHILE : unit terminal
      | T_VAR : unit terminal
      | T_THEN : unit terminal
      | T_SUB : unit terminal
      | T_STRING : (
# 43 "compiler/course_language/Parser.mly"
       (string)
# 841 "compiler/course_language/Parser.ml"
    ) terminal
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
      | T_INT : (
# 44 "compiler/course_language/Parser.mly"
       (int)
# 865 "compiler/course_language/Parser.ml"
    ) terminal
      | T_IF : unit terminal
      | T_ID : (
# 42 "compiler/course_language/Parser.mly"
       (string)
# 871 "compiler/course_language/Parser.ml"
    ) terminal
      | T_GT : unit terminal
      | T_GEQ : unit terminal
      | T_FLOAT_TYP : unit terminal
      | T_FLOAT : (
# 45 "compiler/course_language/Parser.mly"
       (float)
# 879 "compiler/course_language/Parser.ml"
    ) terminal
      | T_EQ : unit terminal
      | T_EOF : unit terminal
      | T_ELSE : unit terminal
      | T_DOT : unit terminal
      | T_DIV : unit terminal
      | T_DEF : unit terminal
      | T_COMMA : unit terminal
      | T_BOOL_TYP : unit terminal
      | T_BOOL : (
# 46 "compiler/course_language/Parser.mly"
       (bool)
# 892 "compiler/course_language/Parser.ml"
    ) terminal
      | T_ASSIGN : unit terminal
      | T_AND : unit terminal
      | T_ADD : unit terminal
    
    type _ nonterminal = 
      | N_main : (Ast.t) nonterminal
      | N_instruction : (Ast.instruction) nonterminal
      | N_function_list : (Ast.function_decl list) nonterminal
      | N_expression : (Ast.expr) nonterminal
    
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
            X (T T_WHILE)
        | 2 ->
            X (T T_VAR)
        | 3 ->
            X (T T_THEN)
        | 4 ->
            X (T T_SUB)
        | 5 ->
            X (T T_STRING)
        | 6 ->
            X (T T_SIZE)
        | 7 ->
            X (T T_SEMICOLON)
        | 8 ->
            X (T T_R_SQ_BRK)
        | 9 ->
            X (T T_R_PAR)
        | 10 ->
            X (T T_R_CUR_BRK)
        | 11 ->
            X (T T_RETURN)
        | 12 ->
            X (T T_PRINT)
        | 13 ->
            X (T T_OR)
        | 14 ->
            X (T T_NULL_TYP)
        | 15 ->
            X (T T_NOT)
        | 16 ->
            X (T T_NEQ)
        | 17 ->
            X (T T_MUL)
        | 18 ->
            X (T T_MOD)
        | 19 ->
            X (T T_L_SQ_BRK)
        | 20 ->
            X (T T_L_PAR)
        | 21 ->
            X (T T_L_CUR_BRK)
        | 22 ->
            X (T T_LT)
        | 23 ->
            X (T T_LEQ)
        | 24 ->
            X (T T_INT_TYP)
        | 25 ->
            X (T T_INT)
        | 26 ->
            X (T T_IF)
        | 27 ->
            X (T T_ID)
        | 28 ->
            X (T T_GT)
        | 29 ->
            X (T T_GEQ)
        | 30 ->
            X (T T_FLOAT_TYP)
        | 31 ->
            X (T T_FLOAT)
        | 32 ->
            X (T T_EQ)
        | 33 ->
            X (T T_EOF)
        | 34 ->
            X (T T_ELSE)
        | 35 ->
            X (T T_DOT)
        | 36 ->
            X (T T_DIV)
        | 37 ->
            X (T T_DEF)
        | 38 ->
            X (T T_COMMA)
        | 39 ->
            X (T T_BOOL_TYP)
        | 40 ->
            X (T T_BOOL)
        | 41 ->
            X (T T_ASSIGN)
        | 42 ->
            X (T T_AND)
        | 43 ->
            X (T T_ADD)
        | _ ->
            assert false
    
    and nonterminal =
      fun nt ->
        match nt with
        | 4 ->
            X (N N_expression)
        | 3 ->
            X (N N_function_list)
        | 2 ->
            X (N N_instruction)
        | 1 ->
            X (N N_main)
        | _ ->
            assert false
    
    and lr0_incoming =
      (8, "\000\01646\bF\004*\020,\022(\018X\n$J&V\028 B\".:0<N\016TLH\026\014\0242>P\030\0068\0124@RD\003\005D\007D\tD")
    
    and rhs =
      ((8, "\00346\bF\004*\020,\022(\018X\n$J&V\028 B\".:0<N\016TLH\026\014\0242>P\030\0068\0124@RD\016\007D\005D\tD"), (8, "\000\001\002\002-.024"))
    
    and lr0_core =
      (8, "\000\001\002\003\004\005\006\007\b\t\n\011\012\r\014\015\016\017\018\019\020\021\022\023\024\025\026\027\028\029\030\031 !\"#$%&'()*+,-./01234")
    
    and lr0_items =
      ((16, "\000\000\016\001\004\001\012\001\012\002\012\003\012\004\012\005\012\006\012\007\012\b\012\t\012\n\012\011\012\012\012\r\012\014\012\015\012\016\012\017\012\018\012\019\012\020\012\021\012\022\012\023\012\024\012\025\012\026\012\027\012\028\012\029\012\030\012\031\012 \012!\012\"\012#\012$\012%\012&\012'\012(\012)\012*\012+\000\001\024\001\024\002\020\001\020\002\028\001\028\002"), (8, "\000\001\002\003\004\005\006\007\b\t\n\011\012\r\014\015\016\017\018\019\020\021\022\023\024\025\026\027\028\029\030\031 !\"#$%&'()*+,-./012345"))
    
    and nullable =
      "\016"
    
    and first =
      (44, "\001\000\000`@\000\016\000\006\004\000\001\000\000\000\000\000\000\000\002\000\000\000\000\000@\000\000")
    
  end) (ET) (TI)
  
end

let main =
  fun lexer lexbuf : (Ast.t) ->
    Obj.magic (MenhirInterpreter.entry `Legacy 0 lexer lexbuf)

module Incremental = struct
  
  let main =
    fun initial_position : (Ast.t) MenhirInterpreter.checkpoint ->
      Obj.magic (MenhirInterpreter.start 0 initial_position)
  
end
