%{
    open Ast
%}

%token IF
%token THEN
%token ELSE
%token WHILE
%token L_PAR
%token R_PAR
%token L_CUR_BRK
%token R_CUR_BRK
%token L_SQ_BRK
%token R_SQ_BRK
%token ADD
%token SUB
%token MUL
%token DIV
%token MOD
%token AND
%token OR
%token NOT
%token EQ
%token NEQ
%token LT
%token GT
%token LEQ
%token GEQ
%token COMMA
%token SEMICOLON
%token ASSIGN
%token DEF
%token DOT
%token PRINT
%token SIZE
%token RETURN
%token INT_TYP
%token FLOAT_TYP
%token BOOL_TYP
%token NULL_TYP
%token VAR
%token <string> ID
%token <string> STRING
%token <int> INT
%token <float> FLOAT
%token <bool> BOOL
%token EOF

%nonassoc THEN
%nonassoc ELSE
%left AND OR
%left EQ NEQ LT GT LEQ GEQ
%left ADD SUB
%left MUL DIV MOD
%nonassoc NOT

%start <Ast.t> main

%%

main:
| l = function_list EOF { Program (List.rev l)}
| i = instruction EOF { Instruction i }
| e = expression EOF { Expression e }

function_list:
| t = function_list f = function_decl { f::t }
| f = function_decl { [f] }

function_decl:
| typ = type_basic name = ID L_PAR param = parameter_list R_PAR DEF body = instruction { Func_decl(typ,name,List.rev param,body,Annotation.create $loc) }

type_basic:
| INT_TYP {TInt}
| FLOAT_TYP {TFloat}
| BOOL_TYP {TBool}
| NULL_TYP {TNull}

parameter_list:
| t = parameter_list COMMA p = parameter { p::t }
| p = parameter { [p] }
|  { [] }

parameter:
| typ = memcell_type name = ID { Value,typ,name }
| VAR typ = memcell_type name = ID { Reference,typ,name }

memcell_type:
| typ = type_basic { Basic(typ) }
| typ = type_basic L_SQ_BRK R_SQ_BRK { Array_t(typ) }

instruction:
| IF test = expression THEN i1 = instruction ELSE i2 = instruction { IfThenElse(test,i1,i2,Annotation.create $loc) }
| IF test = expression THEN i1 = instruction { IfThenElse(test,i1,Block ([],Annotation.create $loc),Annotation.create $loc)}
| WHILE test = expression body = instruction { While(test,body,Annotation.create $loc) }
| name = ID ASSIGN expr = expression SEMICOLON { Affect(name,expr,Annotation.create $loc) }
| L_CUR_BRK l = instruction_list R_CUR_BRK { Block (List.rev l,Annotation.create $loc) }
| name = ID L_SQ_BRK pos = expression R_SQ_BRK ASSIGN expr = expression SEMICOLON { Affect_array(name,pos,expr,Annotation.create $loc) }
| typ = type_basic name = ID L_SQ_BRK size = expression R_SQ_BRK SEMICOLON { Array_decl(typ,name,size,Annotation.create $loc) }
| name = ID L_PAR args = expression_list R_PAR SEMICOLON { Proc(name,List.rev args,Annotation.create $loc) }
| RETURN SEMICOLON { Return (None,Annotation.create $loc) }
| RETURN expr = expression SEMICOLON { Return (Some expr,Annotation.create $loc) }
| PRINT str = STRING SEMICOLON { Print_str (Scanf.unescaped str,Annotation.create $loc) }
| PRINT expr = expression SEMICOLON { Print_expr (expr,Annotation.create $loc) }
| typ = type_basic name = ID SEMICOLON { Var_decl(typ,name,Annotation.create $loc) }

instruction_list:
| t = instruction_list instr = instruction { instr::t }
| { [] }

expression_list:
| expr = expression { [expr] }
| t = expression_list COMMA expr = expression { expr::t }
| { [] }

expression:
| i = INT { Cst_i (i,Annotation.create $loc) }
| f = FLOAT { Cst_f (f,Annotation.create $loc) }
| b = BOOL { Cst_b (b,Annotation.create $loc) }
| s = ID    { Var (s,Annotation.create $loc) }
| e1 = expression b = binop e2 = expression { Binop(b,e1,e2,Annotation.create $loc) }
| u = unop e = expression { Unop(u,e,Annotation.create $loc) } %prec NOT
| name = ID L_SQ_BRK pos = expression R_SQ_BRK { Array_val(name,pos,Annotation.create $loc) }
| name = ID DOT SIZE { Size_tab (name,Annotation.create $loc) }
| name = ID L_PAR args = expression_list R_PAR { Func(name,List.rev args,Annotation.create $loc) }
| L_PAR e = expression R_PAR { e }

%inline binop:
| ADD   { Add }
| SUB   { Sub }
| MUL   { Mul }
| DIV   { Div }
| MOD   { Mod }
| AND   { And }
| OR    { Or }
| EQ    { Eq }
| NEQ   { Neq }
| LT    { Lt }
| GT    { Gt }
| LEQ   { Leq }
| GEQ   { Geq }

%inline unop:
| SUB   { UMin } 
| NOT   { Not }



