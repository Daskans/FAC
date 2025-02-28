
%start <unit> main

%%

main: 
| seq EOF {}
| EOF      {}

seq:
| word seq             {} 
| word                 {}

word: 
| A seq B      {}
| A B           {}


