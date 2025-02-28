%start <unit> main

%%

main:
| s EOF  {}

s:
| A s B s {}
|    {}
