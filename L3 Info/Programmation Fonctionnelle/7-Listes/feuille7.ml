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

(* EXERCICE 7 *)

let l = iota 100000

let time f =
    let start = Sys.time() in
    let _ = f () in
    Sys.time() -. start

(* EXERCICE 8 *)

let l1_1 = []
let l1_2 = [1;2;3;4;5;6]
let l1_3 = [6;5;4;3;2;1]
let l1_4 = [1;2;3;4;50]
let l2 = [8;6;7;4;1;2;3;9;5]

let rec list_subset l1 l2 =
    match l1 with
    | [] -> true
    | (head::tail) -> List.mem head l2 && list_subset tail l2

let test =
    begin
        assert(list_subset l1_1 l2 = true);
        assert(list_subset l1_2 l2 = true);
        assert(list_subset l1_3 l2 = true);
        assert(list_subset l1_4 l2 = false);
    end
;;

(* EXERCICE 9 *)

(* EXERCICE 10 *)

let pref1 = []
let pref2 = [1;2;3]
let l1 = [1;2;3]
let l2 = [1;2]
let l3 = [1;2;3;4]
let l4 = [4;1;2;3]

let rec is_prefixe list1 list2 =
    match list1, list2 with
    | [], _ -> true
    | (head1::tail1), (head2::tail2) -> (head1 = head2) && is_prefixe tail1 tail2
    | _, [] -> false

let test =
    begin
        assert(is_prefixe pref1 l1 = true);
        assert(is_prefixe pref2 l1 = true);
        assert(is_prefixe pref2 l2 = false);
        assert(is_prefixe pref2 l3 = true);
        assert(is_prefixe pref2 l4 = false);
    end
;;

(* EXERCICE 11 *)

let rec squares list = 
    match list with
    | [] -> []
    | (head::tail) ->  [(head*head)] @ (squares tail)

let test =
    begin
        assert(squares [] = []);
        assert(squares [1;2;3] = [1;4;9]);
    end
;;

(* EXERCICE 12 *)

let rec sum list = match list with | (head::[]) -> head | (head::tail) -> head + (sum tail) | [] -> failwith "NULL"

let rec prod list = match list with | (head::[]) -> head | (head::tail) -> head * (prod tail) | [] -> failwith "NULL"

let test =
    begin
        assert(sum [1;2;3;4] = 10);
        assert(prod [1;2;3;4] = 24);
    end
;;

(* EXERCICE 13 *)

(* 1) ('a -> bool) 'a list -> a' list * a' list*)

(* 2) la fonction n'a pas UNE valeure en générale ??? elle renvoit un couple de liste *)

(* 3) *)

let breakfast p list =
    let rec aux p list result =
        match list, result with
        | [],_ -> result
        | (head::tail), (l1, l2) -> if p head then
                                        aux p tail ((l1 @ [head]), l2)
                                    else
                                        aux p tail (l1, (l2 @ [head]))
    ;
    in aux p list ([],[])


let test =
    begin
        assert(breakfast (fun x -> x mod 2 = 0) [1;2;3;4;5;6;7;8;9] = ([2;4;6;8],[1;3;5;7;9]));
    end
;;