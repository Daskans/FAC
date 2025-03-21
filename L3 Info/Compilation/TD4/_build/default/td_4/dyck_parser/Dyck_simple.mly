
%start <unit> main

%%

main: 
| word EOF {}
| EOF      {}

word: 
| word word         {}
| A word B      {}
| A B           {}


