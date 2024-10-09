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
