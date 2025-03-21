%start <unit> main

%%

main:
| s EOF  {}

s:
| s A s B {}
|    {}
