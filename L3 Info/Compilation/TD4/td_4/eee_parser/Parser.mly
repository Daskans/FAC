%token ADD SUB
%token MUL DIV REC
%token LPAR RPAR
%token <int> INT
%token EOF

%start <unit> main

%left ADD
%left MUL

%%

main:
| s EOF {}
| EOF {}

%inline u:
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



