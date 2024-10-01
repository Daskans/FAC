(*type couple = C of int * int;;*)

type couple = bool -> int;;

let make_couple a b =
    fun bool ->
        if bool = true then
            a
        else
            b
;;

let c1 = make_couple 1 2;;
let c2 = make_couple 3 4;;

let couple_fst c = c true ;;

let couple_snd c = c false ;;

let couple_sum c = (couple_fst c) + (couple_snd c);;

let couple_add c1 c2 = make_couple ((couple_fst c1) + (couple_fst c2)) ((couple_snd c1) + (couple_snd c2)) ;;

let pair_of_couple c = (couple_fst c, couple_snd c);;


