(* EXERCICE 1 *)

type ('k, 'v) dict = ('k * 'v) list

let empty_dict : ('k,'v) dict = []
let test_dict_1 : ('k,'v) dict = [(1,2);(2,6);(3,42)]
let test_dict_2 : ('k,'v) dict =
    [("grenouille","le terme grenouille est un nom vernaculaire attribué à certains amphibiens, principalement dans le genre rana");
    ("idée","j'en ai plus")]
let test_dict_3 : ('k,'v) dict = [(1,"un");(2,"deux")]

(* EXERCICE 2 *)

let rec find key (dict : ('k,'v) dict) =
    match dict with
    | [] -> None
    | (k, v)::tail ->
        if k = key then
            Some(v)
        else
            find key tail


let rec add key value (dict : ('k,'v) dict) =
    match dict with
    | [] -> (key,value)::dict
    | (k,v)::tail ->
        if k = key then
            (k,value)::tail
        else
            (k,v)::add key value tail


let rec remove key (dict : ('k,'v) dict) =
    match dict with
    | [] -> dict
    | (k,v)::tail ->
        if k = key then
            remove key tail
        else
            (k,v)::remove key tail


(* EXERCICE 5*)

(* find est en O(n), je ne sais pas comment réduire la compléxité*)


let test =
    begin
        assert(find 1 test_dict_1 = Some(2));
        assert(find "idée" test_dict_2 = Some("j'en ai plus"));
        assert(find 1 test_dict_3 = Some("un"));
        assert(add 4 25 test_dict_1 = [(1,2);(2,6);(3,42);(4,25)]);
        assert(add "grenouille" "trop long" test_dict_2 = [("grenouille","trop long");("idée","j'en ai plus")]);
        assert(add 3 "trois" test_dict_3 = [(1,"un");(2,"deux");(3,"trois")]);
        assert(remove 2 test_dict_1 = [(1,2);(3,42)]);
        assert(remove "grenouille" test_dict_2 = [("idée","j'en ai plus")]);
        assert(remove 2 test_dict_3 = [(1,"un")]);
    end
;;