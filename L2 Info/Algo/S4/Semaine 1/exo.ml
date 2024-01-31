(*EXERCICE 1*)

type ('a,'b,'c)tupple3 = Triplet of 'a * 'b * 'c;;

let trip = Triplet(1,2,3);;

let triplet_fst triplet =
    match triplet with
    | Triplet(a,_,_) -> a
;;

let triplet_snd triplet =
    match triplet with
    | Triplet(_,b,_) -> b
;;

let triplet_thd triplet =
    match triplet with
    | Triplet(_,_,c) -> c
;;

(*exercice 2*)
type 'a list = [] | List of 'a * 'a list;;

(*ARBRE BINARE 2.3*)
type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

let tree = Node(8,Node(6,Node(7,Empty,Empty),Node(999,Node(5,Node(2,Empty,Empty),Empty),Node(8,Empty,Empty))),Node(16,Node(12,Empty,Empty),Empty));;

let btree_root t =
    match t with
    | Empty -> failwith "empty tree"
    | Node(head,_,_) -> head
;;

(*exercice 7*)

let rec btree_mem t i =
    match x with
    | btree t -> true
    | btree_mem