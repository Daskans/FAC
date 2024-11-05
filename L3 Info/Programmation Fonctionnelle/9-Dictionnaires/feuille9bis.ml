(* EXERCICE 1 *)

type 'a option = Some of 'a | None

type ('k, 'v) dict = 'k -> 'v option

let empty_dict : ('k, 'v) dict = fun k -> None

let find key (dict : ('k, 'v) dict) : 'v option =
    dict key

let add key value (dict : ('k, 'v) dict) : ('k, 'v) dict =
    fun k ->
        if k = key then
            Some(value) 
        else
            dict k

let remove key (dict : ('k, 'v) dict) : ('k, 'v) dict =
    fun k ->
        if k = key then
            None
        else
            dict k

let rec dict_from_list list =
    match list with
    | [] -> empty_dict
    | (key, value)::tail -> add key value (dict_from_list tail)


let week_list = [(1,"Lundi"); (2,"Mardi"); (4,"Jeudi")]
let week_dict = dict_from_list week_list;;
    

(* EXERCICE 2 *)

type 'a option = Some of 'a | None

type ('k, 'v) dict = ('k * 'v option) list

let empty_dict : ('k, 'v) dict = []
let not_so_empty_dict : ('k,'v) dict = [(1,Some("Lundi")); (2,Some("Mardi")); (3,Some("Jeudi"))]

let rec find key (dict : ('k, 'v) dict) =
    match dict with
    | [] -> None
    | head::tail ->
        if key = fst head then
            snd head
        else
            find key tail

let add_or_update key value (dict : ('k, 'v) dict) =
    (key, Some(value))::dict

let remove key (dict : ('k, 'v) dict) =
    let rec aux result =
        match result with
        | [] -> dict
        | head::tail ->
            if fst head = key then
                (key, None)::dict
            else
                aux tail
    in aux dict
;;

(* EXERCICE 4 *)

