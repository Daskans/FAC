(* EXERCICE 2 *)

type date = { day : int; month : int; year : int};;

let today = {day = 1; month = 10; year = 2024};;
let not_today = {day = 24; month = 3; year = 2024};;

let date_infeg date1 date2 =
    if date1.year < date2.year then
        true
    else if date1.month < date2.month then
        true
    else if date1.month = date2.month then
        if date1.day < date2.day then
            true
        else false
    else
        false
;;

(* EXERCICE 3 *)

type 'a mylist = | C of 'a * 'a mylist | Nil ;;

let l_nil = Nil;;
let l_test = (C(0, C(1, C(3, C(4, C(5, Nil))))));;

let rec mylist_length list =
    match list with
    | Nil -> 0
    | C(head, tail) -> 1 + mylist_length tail
;;

let rec interval_list n p =
    if n > p then
        Nil
    else if n = p then
        C(p, Nil)
    else
        C(n, (interval_list (n+1) p))
;;

let rec map f list =
    match list with
    | Nil -> Nil
    | C(head, tail) -> C(f(head), map f tail)
;;

let rec filter pred list =
    match list with
    | Nil -> Nil
    | C(head, tail) -> if pred(head) then
                            C(head, filter pred tail)
                        else
                            filter pred tail
;;

(* EXERCICE 4 *)

type peano = | Zero | Succ of peano;;

let one = Succ(Zero);;
let two = Succ(Succ(Zero));;
let three = Succ(Succ(Succ(Zero)));;

let rec sum_p m n =
    match n with
    | Zero -> m
    | Succ(peano) -> sum_p (Succ(m)) peano
;;

let mult_p m n =
    let rec mult_aux m n result =
        match n with
        | Zero -> result
        | Succ(peano) -> mult_aux m peano (sum_p result m)
    ;
    in mult_aux m n Zero
;;

let rec peano_of_int n =
    if n = 0 then
        Zero
    else
        Succ(peano_of_int (n-1))
;;

let rec int_of_peano peano =
    match peano with
    | Zero -> 0
    | Succ(n) -> 1 + int_of_peano n
;;

(* EXERCICE 5 *)

let terminal_factorial n =
    let rec factorial_aux n result =
        if n = 0 then
            1
        else if n = 1 then
            result
        else 
            factorial_aux (n-1) (result * (n-1))
    ;
    in factorial_aux n n
;;

(* EXERCICE 6 *)

let terminal_sum n p =
    let rec sum_aux n p result =
        if n > p then
            failwith "ERROR"
        else if n = p then
            result
        else
            sum_aux n (p-1) (result + (p-1))
    ;
    in sum_aux n p p
;;

(* EXERCICE 7 *)

let terminal_list_length list =
    let rec length_aux list result =
        match list with
        | Nil -> result
        | C(head, tail) -> length_aux tail 1+result
    ;
    in length_aux list 0
;;

(* EXERCICE 8 *)

let terminal_interval_list n p =
    if n > p then
        Nil
    else
        let rec interval_aux n p list=
            if n = p then
                list
            else
                interval_aux n (p-1) (C((p-1), list))
    ;
    in interval_aux n p (C(p, Nil))
;;
