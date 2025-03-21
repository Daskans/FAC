
%start <unit> main

%%

main: 
| seq EOF {}
| EOF      {}

seq:
| seq word             {} 
| word                 {}

word: 
| A seq B      {}
| A B           {}


