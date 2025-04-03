%token ADD SUB
%token MUL DIV REC
%token LPAR RPAR
%token USUB
%token <int> INT
%token EOF

%start <unit> main

%left ADD SUB
%left MUL DIV

%nonassoc REC
%nonassoc USUB

%%

main:
| expr=e EOF {Format.printf "Result : %d\n"expr}
| EOF {()}

e:
| expr1=e ADD expr2=e       {expr1 + expr2}
| expr1=e SUB expr2=e       {expr1 - expr2}
| SUB expr=e %prec USUB     {- expr}
| expr1=e MUL expr2=e       {expr1 * expr2}
| expr1=e DIV expr2=e       {expr1 / expr2}
| expr=e REC                {expr}
| LPAR expr=e RPAR          {expr}
| expr=INT                  {expr}


