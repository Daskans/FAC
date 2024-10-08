(* Écrire une fonction sum n p récursive terminale qui prend en paramètre deux entiers n 
et p et retourne la somme des entiers contenus dans l'intervalle fermé [n,p]; 
en particulier si l'intervalle est vide la fonction retourne 0
Remarque: la somme sur un intervalle vide est nulle.*)

let sum n p =
    let rec sum_aux n p result =
        if n > p then
            0
        else if n = p then
            result
        else
            sum_aux n (p-1) (result + (p-1))
    ;
    in sum_aux n p p
;;