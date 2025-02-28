%token ADD SUB
%token MUL DIV REC
%token LPAR RPAR
%token <int> INT
%token EOF

%start <unit> main

%%

main:
| s EOF {}
| EOF {}

u:
| ADD   {}
| SUB   {}
| MUL   {}
| DIV   {}


s:
| INT  {}
| s u s {}
| s REC {}
| SUB s  {}
| LPAR s RPAR {}



