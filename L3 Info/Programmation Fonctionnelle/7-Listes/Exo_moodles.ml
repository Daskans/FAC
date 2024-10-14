(* Écrire une fonction iota_r de type  int -> int list telle que iota_r n renvoie la liste [n; n-1; ...; 1]. *)

(* Écrire une fonction rotate_left de type  'a list -> 'a list telle que rotate_left [e1; e2; ... ; en] renvoie la liste [e2;...; en; e1]. *)

let rotate_left list =
    match list with
    | [] -> []
    | (head::tail) -> tail @ [head]
;;

(* Écrire une fonction list_to_pairs l de type  'a list -> ('a * int) list 
qui retourne une liste dont les éléments sont les paires (e, k) 
où e est une élément de l et k son nombre d'occurrences dans l. 
L'ordre des paires n'est pas important.

Exemple : list_to_pairs [1; 1; 2; 2; 5; 1; 1; 42; 2] renvoie la liste [(1, 4); (2, 3); (5, 1); (42, 1)]. 
On pourra utiliser des fonctions auxiliaires et des fonctions du module List. *)




(* fonction split list
list -> [list pair] [lists impair] *)

let pred_1 = (fun x -> x mod 2 = 0)

let split pred list =
    let rec split_aux list list_pred list_not_pred =
        match list with
        | [] ->(list_pred,list_not_pred)
        | (head::tail) -> if pred head then
                            split_aux tail (list_pred @ [head]) list_not_pred
                        else
                            split_aux tail list_pred (list_not_pred @ [head])
    ;
    in split_aux list [] []
;;


(* mapcan *)

let rec mapcan alteration list =
    match list with
    | [] -> []
    | (head::tail) -> (alteration head) @ (mapcan alteration tail)
;;

mapcan (fun x -> [x; x*x; x*x*x]) [1; 2; 3];;

(* prefix *)

let prefix list n =
    if n < 0 then []
    else let rec prefix_aux list n result =
        match list with
        | [] -> result
        | (head::tail) -> if n = 0 then
                            result
                        else
                            prefix_aux tail (n-1) (result @ [head])
    ;
    in prefix_aux list n []
;;

prefix [1; 2; 3; 4] 2;;

(* suffix *)

let suffix list n =
    List.rev (prefix (List.rev list) n)
;;