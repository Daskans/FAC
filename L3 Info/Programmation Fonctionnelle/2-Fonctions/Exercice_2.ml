(* Écrire une fonction sum n p qui prend en paramètre deux entiers n et  p 
et retourne la somme des entiers contenus dans l'intervalle fermé [n,p]; 
en particulier si l'intervalle est vide la fonction retourne 0
Remarque: la somme sur un intervalle vide est nulle.*)

let rec sum n p = 
    if n > p then
        0
    else 
        n + sum (n + 1) p
;