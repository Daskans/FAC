(* Nom: BALAVOINE *)
(* Prénom: Kyrian *)
(* Groupe: INF501A4 *)

(*** Section 1: Préléminaires ***)
(** 1- remove_duplicates récursive terminale **)
let list = [2; 1; 3; 1; 4; 5; 2]

let rec is_in_list l x =
    match l with
    | [] -> false
    | head::tail ->
        if head = x then
            true
        else
            is_in_list tail x
            


let remove_duplicates l =
    let rec aux list result =
        match list with
        | [] -> result
        | head::tail ->
            if not(is_in_list result head) then
                aux tail (head::result)
            else
                aux tail result
    in aux (List.rev l) []
(* 'a list -> 'a list *)

(** 2- pairs_flatten récursive terminale **)
let pairs = [(1, 2); (2, 3); (3, 4); (2, 3)]

let pairs_flatten pairs =
    let rec aux couples result =
        match couples with
        | [] -> List.rev result
        | (first, second)::tail -> aux tail (second::(first::result))
    in aux pairs []

(* ('a * 'a) list -> 'a list *)

(** 3- exists **)
let exists predicate l =
    let rec aux list bool =
        match list with
        | [] -> bool
        | head::tail -> aux tail (predicate head)
    in aux l false
(* ('a -> bool) -> 'a list -> bool *)

(*** Section 2: Arcs ***)
type arc = A of int * int


(** 4- constructeur/accesseurs pour type arc **)
let make_arc origin extremity =
    A(origin, extremity)
(* int -> int -> arc *)
    
let ex_arc = make_arc 4 3

let arc_origin arc =
    match arc with
    | A(origin, _) -> origin
(* arc -> int *)

let arc_extremity arc =
    match arc with
    | A(_, extremity) -> extremity
(* arc -> int *)

(** 5- reverse_arc **)
let reverse_arc arc =
    make_arc (arc_extremity arc) (arc_origin arc)
(* arc -> arc *)

(** 6- pair_to_arc **)
let pair_to_arc pair =
    make_arc (fst pair) (snd pair)
(* int * int -> arc *)

(** 7- arc_to_pair **)
let arc_to_pair arc =
    (arc_origin arc, arc_extremity arc)
(* arc -> int * int *)  

(** 8- pairs_to_arcs **)
let pairs_to_arcs pairs =
    let rec aux list result =
        match list with
        | [] -> List.rev result
        | head::tail -> aux tail ((pair_to_arc head)::result)
    in aux pairs []
(* (int * int) list -> arc list *)

(** 9- arcs_to_pairs arcs **)
let arcs_to_pairs arcs =
    let rec aux list result =
        match list with
        | [] -> List.rev result
        | head::tail -> aux tail ((arc_to_pair head)::result)
    in aux arcs []
(* arc list -> (int * int) list *)


(*** Section 3: Graphes ***)
type graph = { arcs : arc list; isolated_nodes : int list }
(** 10- Constructeur/accesseurs pour le type graph **)

let make_graph arcs isolated_nodes =
    { arcs = arcs; isolated_nodes = isolated_nodes}
(* arc list -> int list -> graph *)
  
let graph_arcs graph =
    match graph with
    | {arcs;_} -> arcs
(* graph -> arc list *)
    
let graph_isolated_nodes graph =
    match graph with
    | {arcs;isolated_nodes} -> isolated_nodes
(* graph -> int list *)

(** 11- **)
let pairs = [(1, 2); (1, 3); (3, 4); (4, 1); (5, 6)]
let arcs = pairs_to_arcs pairs
let mygraph = make_graph arcs [7]

(** 12- Visualisation - facultatif **)
(* #use "dot.ml" *)
(* graph_view mygraph *)

(** 13- nodes_from_arcs **)
let nodes_from_arcs arcs =
    remove_duplicates (pairs_flatten (arcs_to_pairs arcs))
(* arc list -> int list *)

(** 14- graph_nodes **)
let graph_nodes graph =
    (nodes_from_arcs (graph_arcs graph)) @ graph_isolated_nodes graph
(* graph -> int list *)

(** 15- node_neighbours **)
let node_neighbours node arcs =
    let rec aux list result =
        match list with
        | [] -> List.rev result
        | head::tail ->
            if (arc_origin head) = node then
                aux tail ((arc_extremity head)::result)
            else
                aux tail result
    in aux arcs []
(* int -> arc list -> int list *)

(** 16- mark_from_nodes *)
let mark_from_nodes nodes arcs marked =
    let rec aux list result =
        match list with
        | [] -> remove_duplicates (marked @ result)
        | head::tail ->
            let rec aux2 list result2 =
                match list with
                | [] -> result2
                | head2::tail2 ->
                    if is_in_list result head2 || is_in_list result2 head2 then
                        aux2 tail2 result2
                    else
                        aux2 tail (head2::result2)
            in aux tail (head::(aux2 (node_neighbours head arcs) []) @ result)
    in aux nodes []
            
(*  int list -> arc list -> int list -> int list *)

(** 17- mark_from_node **)
(* let mark_from_node node arcs = *)
(* int -> arc list -> int list *)

(** 18- unorient_arcs arcs **)
let unorient_arcs arcs =
    let rec aux list result =
        match list with
        | [] -> result
        | head::tail -> aux tail ((head)::(reverse_arc head::result))
    in aux arcs []
(* arc list -> arc list *)

(** 19- graph_connected_p **)
(* graph_connected_p graph = *)
(* graph -> bool *)

(** 20- graph_has_circuit **)
(* let graph_has_circuit_p graph = *)
(* graph -> bool *)