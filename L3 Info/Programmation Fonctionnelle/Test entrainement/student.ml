(* Nom: BALAVOINE*)
(* Prenom: Kyrian*)
(* Groupe: A4 *)

let l = [0;1;2;3;4]

(* 1 /2 *)               
let make_list n e = 
    let rec aux result x =
        if x = n then
            result
        else
            aux (e::result) (x+1)
    in aux [] 0 

(* 2 /1 *)
let make_zeros n =
    make_list n 0

(* 3 /1.5*)
let get_nth l i =
    let rec aux rest x =
        match rest with
        | [] -> failwith "hd"
        | head::tail ->
            if x = i then
                head
            else
                aux tail (x+1)
    in aux l 0

(* 4 /2 *)
let set_nth l i e =
    let rec aux result rest x =
    match rest with
    | [] -> failwith "tl"
    | head::tail ->
        if x = i then
            (List.rev (e::result)) @ tail
        else
            aux (head::result) tail (x+1)
    in aux [] l 0

    

(* 5 /2*)
let get_nth_opt l i =
    let rec aux rest x =
        match rest with
        | [] -> None
        | head::tail ->
            if x = i then
                Some(head)
            else
                aux tail (x+1)
    in aux l 0


type grid = int list list

(* 6 /2 *)
let make_empty_grid size : grid  =
    let rec aux result x =
        if x = size then
            result
        else
            aux ((make_zeros size)::result) (x+1)
    in aux [] 0
        
let grid = make_empty_grid 4

(* 7 /0.5*)
let grid_size grid =
    match grid with
    | [] -> 0
    | line::rest ->
        let rec aux line x =
            match line with
            | [] -> x
            | head::tail ->
                aux tail (x+1)
        in aux line 0

(* 8 /1*)
let correct_z_p grid z =
    grid_size grid > z && z>= 0

(* 9 /1*)
let correct_coor_p grid li co =
    correct_z_p grid li && correct_z_p grid co

  
(* 10 /1.5*)
let get_square grid li co =
    get_nth (get_nth grid li) co

(* 11 /2 *)
let set_square grid li co e =
    set_nth grid li (set_nth (get_nth grid li) co e)


(* 12 /0.5 *)
let pred_square_p pred grid li co =
    pred (get_square grid li co)

(* 13 /1 *)
let zero_square_p grid li co =
    pred_square_p (fun x -> x = 0) grid li co
  
(* 14 /2*)
let grid_map f grid =
    let rec aux max li co result =
        if li = max then
            result
        else if co = max then
            aux max (li+1) 0 result
        else
            aux max li (co+1) (set_square result li co (f(get_square grid li co)))
    in aux (grid_size grid) 0 0 grid


