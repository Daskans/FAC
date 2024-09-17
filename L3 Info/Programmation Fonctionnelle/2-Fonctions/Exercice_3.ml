(* Écrire une fonction op_prod n p f op neutral qui prend en paramètre deux entiers n et  p,  
une fonction f de type int -> 'a,  
une fonction associative op de type  'a -> 'a -> 'a et neutral de type 'a l'élément neutre de  op et 
qui retourne neutral si l'intervalle est vide, f(n ) OP f(n+1) ... OP f(p), sinon.

Remarque: l'opération sur un intervalle vide doit retourner l'élément neutre.

Exemples:*)

op_prod 1 3 (fun x -> x ) ( + ) 0 (* - : int = 6 *)
op_prod 1 4 (fun x -> x ) ( * ) 1 (* - : int = 24 *)
op_prod 1 4 (fun i -> String.make 1 (char_of_int (i + 96))) (^) "" (* - : string = "abcd" *)

let rec op_prod n p f op neutral = 
    if n > p then
        neutral
    else
        op (f n) (op_prod (n+1) p f op neutral)
;;