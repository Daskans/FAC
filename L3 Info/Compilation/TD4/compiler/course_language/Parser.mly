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

%start <Ast.t> main

%%

main:
| l = function_list EOF { Program (List.rev l) (*Le List.rev est là si vous construisez la liste à l’envers (ce qui arrive si vous le faites avec une associativité à gauche (si vous voulez que l’arbre reste petit)). Si vous la construisez dans le bon sens, retirez le List.rev.*)}
| i = instruction EOF { Instruction i }
| e = expression EOF { Expression e }

function_list:
|  {[]}
| IF THEN ELSE WHILE L_PAR R_PAR L_CUR_BRK R_CUR_BRK L_SQ_BRK R_SQ_BRK ADD SUB MUL DIV MOD AND OR NOT EQ NEQ LT GT LEQ GEQ COMMA SEMICOLON ASSIGN DEF DOT PRINT SIZE RETURN INT_TYP FLOAT_TYP BOOL_TYP NULL_TYP VAR ID STRING INT FLOAT BOOL EOF { (*À retirer -- ici pour éviter les warnings avant de commencer*) []}

instruction:
| SEMICOLON {Block ([],Annotation.create $loc) }

expression:
| i = INT { Cst_i (i,Annotation.create $loc) }



