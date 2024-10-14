(* EXERCICE 1 *)

type 'a mylist = | C of 'a * 'a mylist | Nil

let l_nil = Nil
let my_list = (C(0, C(1, C(3, C(4, C(5, Nil))))))
let list = [0;1;3;4;5]

let rec mylist_length list =
    match list with
    | Nil -> 0
    | C(head, tail) -> 1 + mylist_length tail


let rec interval_list n p =
    if n > p then
        Nil
    else if n = p then
        C(p, Nil)
    else
        C(n, (interval_list (n+1) p))


let rec map f list =
    match list with
    | Nil -> Nil
    | C(head, tail) -> C(f(head), map f tail)


let rec filter pred list =
    match list with
    | Nil -> Nil
    | C(head, tail) -> if pred(head) then
                            C(head, filter pred tail)
                        else
                            filter pred tail


let rec list_of_mylist list =
    match list with
    | Nil -> []
    | C(head, tail) -> head :: (list_of_mylist tail)


let rec mylist_of_list list =
    match list with
    | [] -> Nil
    | head :: tail -> C(head, mylist_of_list tail)


let test =
    begin
        assert(list_of_mylist my_list = list);
        assert(mylist_of_list list = my_list);
    end
;;

(* EXERCICE 2 *)

let rec replicate x k =
    if k = 0 then
        []
    else
        x :: (replicate x (k-1))


let terminal_replicate x k =
    let rec replicate_aux x k result =
        if k = 0 then
            result
        else
            replicate_aux x (k-1) (x::result)
    ;
    in replicate_aux x k []


let test =
    begin
        assert(replicate 2 0 = []);
        assert(replicate 1 4 = [1;1;1;1]);
        assert(terminal_replicate 1 4 = [1;1;1;1]);
    end
;;

(* EXERCICE 3 *)

let list = [0;1;2;3;4;5]
let rev_list = [5;4;3;2;1;0]

let rec reverse list =
    match list with
    | [] -> []
    | head::tail -> reverse tail @ [head]

(* O(n²)*)


let terminal_reverse list =
    let rec reverse_aux list result =
        match list with
        | [] -> result
        | head::tail -> reverse_aux tail (head::result)
    ;
    in reverse_aux list []

(* O(n)*)


let test =
    begin
        assert(reverse list = rev_list);
        assert(terminal_reverse list = rev_list);
    end
;;

(* EXERCICE 4 *)

let rec iota_r n =
    if n = 1 then
        [1]
    else
        n :: (iota_r (n-1))

(* O(2n) -> O(n) *)

let rec iota n =
    if n = 1 then
        [1]
    else
        (iota (n-1)) @ [n]

(* O(n²) *)

let terminal_iota_r n =
    let rec iota_r_aux k result =
        if k = n then
            k :: result
        else
            iota_r_aux (k+1) (k::result)
    ;
    in iota_r_aux 1 []

let terminal_iota n =
    let rec iota_aux n result =
        if n = 1 then
           1 ::  result
        else
            iota_aux (n-1) (n::result)
    ;
    in iota_aux n []

let test =
    begin
        assert(iota_r 5 = [5;4;3;2;1]);
        assert(iota 5 = [1;2;3;4;5]);
        assert(terminal_iota_r 5 = [5;4;3;2;1]);
        assert(terminal_iota 5 = [1;2;3;4;5]);
    end
;;

(* 4.6) avec une complexité de O(n²), une latence se fait ressentire dès n = 4000 *)

(* EXERCICE 5 *)

let l_member = [1;2;3;4;5]

let rec member x list =
    match list with
    | [] -> false
    | head::tail -> if head = x then
                        true
                    else
                        false || member x tail

let test =
    begin
        assert(member 1 l_member = true);
        assert(member 11 l_member = false);
        assert(member 1 [] = false);
    end
;;

(* 5.2) 'a -> 'a list -> bool *)

(* 5.3) Le code est pratiquement le même à l'exeption de la comparaison head = x qui est une comparaison structurelle
dans le mem original. Mon code est cependant identique à memq *)

(* EXERCICE 6 *)

let l_count = [1;1;1;2;3;1]

let rec count x list =
    match list with
    | [] -> 0
    | head::tail -> if head = x then
                        1 + count x tail
                    else
                        count x tail


(* 6.2) 'a -> 'a list -> int *)

let member' x list = count x list > 0

let test =
    begin
        assert(count 1 l_count = 4);
        assert(count 4 l_count = 0);
        assert(member' 1 l_count = true);
        assert(member' 4 l_count = false);
    end
;;