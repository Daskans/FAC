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