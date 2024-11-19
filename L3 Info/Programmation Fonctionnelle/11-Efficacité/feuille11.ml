(* EXERCICE 1 *)

(* la fonction append a autant d'appel qu'il y a d'entrée dans l1 + 1*)

(* 2 fois la longueur de l1 + 1 *)

(* plus tard *)

(* plus tard *)


(* EXERCICE 2 *)

(* elle append reverse l au début de acc *)

let rec rev_append l acc =
    match l with
    | [] -> acc
    | h :: t -> rev_append t (h :: acc)

let reverse_efficace l =
    rev_append l []
;;

(* c'est basiquement une réccursivité terminale *)


(* EXERCICE 3 *)

type e_b_c = I of int | B of bool | S of string

let list : e_b_c list = [I(12); B(true); S("helo"); I(8); S("word")]

let somme l =
    let rec aux l result =
        match l with
        | [] -> result
        | I(head)::tail -> aux tail (head + result)
        | _::tail -> aux tail result
    in aux l 0

let filtre_int l =
    let rec aux l result =
        match l with
        | [] -> List.rev result
        | I(head)::tail -> aux tail (head :: result)
        | _::tail -> aux tail result
    in aux l []

let concat l =
    let rec aux l result =
        match l with
        | [] -> result
        | S(head)::tail -> aux tail (String.cat result head)
        | _::tail -> aux tail result
    in aux l ""

let test =
    begin
        assert(somme list = 20);
        assert(filtre_int list = [12;8]);
        assert(concat list = "heloword");
    end
;;

(* EXERCICE 4 *)

