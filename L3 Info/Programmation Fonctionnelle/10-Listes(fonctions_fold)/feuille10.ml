(* EXERCICE 1 *)

let rec right_fold op list accumulator =
    match list with
    | [] -> accumulator
    | head::tail -> op head (right_fold op tail accumulator)


let rec left_fold op accumulator list =
    let rec aux accumulator list =
        match list with
        | [] -> accumulator
        | head::tail -> op (left_fold op accumulator tail) head
    in aux accumulator (List.rev list)


let test =
    begin
        assert(right_fold (fun x y -> x + y) [1;2;3;4] 0 = 10);
        assert(right_fold (fun x y -> x - y) [1;2;3;4] 0 = -2);
        assert(left_fold (fun x y -> x + y) 0 [1;2;3;4] = 10);
        assert(left_fold (fun x y -> x - y) 0 [1;2;3;4] = -10);
    end
;;

(* EXERCICE 2 *)

let length l =
    List.fold_right (fun x y ->  (int_of_float ( float_of_int x ** 0.)) + y ) l 0
;;

let rec reverse l =
    List.fold_left (fun result x -> x::result) [] l
;;

let maximum l =
    List.fold_right (fun x y -> if x > y then x else y) l min_int
;;

let filter p l =
    List.fold_right (fun l result -> if p l then l::result else result) l []
;;

let remove_duplicates l =
    List.fold_right (fun x result -> if List.mem x result then result else x::result ) l []
;;

let append list1 list2 =
    List.fold_right (fun x result -> x::result) list1 list2
;;

let map f l =
    List.fold_right (fun x result-> (f x)::result) l []
;;