(* Écrire une fonction convolution f g qui prend en paramètre deux fonctions f et g,
de type int -> int chacune et qui retourne la fonction de type int -> int qui à n associe  
f(0)g(n )+f(1)g(n-1)+ ...+ f(i)g(n-i) + ... + f(n )g(0). 
On pourra écrire une fonction auxiliaire sum_product f g i j qui calcule la somme de k = i à j des f(k)g(j-k).

Exemples:*)

convolution (fun x -> x) (fun x -> x) 3 (* = 4 *)
convolution (fun x -> 2 * x) (fun x -> x * x) 5 (* = 100 *)
convolution (fun x -> 1) (fun x -> x) 10  (* = 55 *)

let rec sum_product f g i j =
    if j < 0 then 
        0
    else
        (f(i) * g(j)) + (sum_product f g (i+1) (j-1))
;;



let convolution f g n =
    sum_product f g 0 n
;;

