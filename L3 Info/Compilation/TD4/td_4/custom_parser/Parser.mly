%token A
%token B
%token EOF

%start <unit> main

%%

main:
| s EOF  {}
| EOF    {}

s:
| A s B {}
| A B   {}
