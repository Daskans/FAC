%token ADD SUB
%token MUL DIV REC
%token LPAR RPAR
%token <int> INT
%token EOF

%start <unit> main

%%

main:
| EOF         {}
| ADD SUB MUL DIV REC LPAR RPAR INT EOF { (* À enlever -- ici pour éviter des warnings !*)}

