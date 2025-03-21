%token ADD SUB
%token MUL DIV REC
%token LPAR RPAR
%token <int> INT
%token EOF

%start <unit> main

%%

main:
| e EOF       {}
| EOF         {}

e:
| e ADD t       {}
| SUB t         {}
| t

t:
| t MUL f       {}
| t DIV f       {}
| t REC         {}
| f

f:
| LPAR e RPAR   {}
| INT           {}