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

let rec list_length l =
    match l with
    | [] -> 0
    | List(_,tail) -> 1 + list_length tail
;;

let rec list_nb_occurence e l =
    match l with
    | [] -> 0
    | List(head,tail) -> if head = e then 1 + list_nb_occurence e tail else list_nb_occurence e tail
;;

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

let btree_left t =
    match t with
    | Empty -> failwith "empty tree"
    | Node(_,left,_) -> left
;;

let btree_right t =
    match t with
    | Empty -> failwith "empty tree"
    | Node(_,_,right) -> right
;;

(*exercice 7*)

let rec btree_mem t x =
    match t with
    | Empty -> false
    | Node(head,left,right) -> if head = x then true else btree_mem left x || btree_mem right x
;;

(*exercice 8*)

let rec btree_nb_occ x t = 
    match t with
    | Empty -> 0
    | Node(head,left,right) -> if head = x then 1 + btree_nb_occ x left + btree_nb_occ x right else btree_nb_occ x left + btree_nb_occ x right
;;

(*exercice Moodle*)

let arity t = 
    match t with
    | Empty -> 0
    | Node(_,Empty,Empty) -> 0
    | Node(_,Empty,_) -> 1
    | Node(_,_,Empty) -> 1
    | Node(_,_,_) -> 2
;;

let rec btree_size t = 
    match t with
    | Empty -> 0
    | Node(head,left,right) -> 1 + btree_size left + btree_size right
;;

let rec btree_height t = 
    match t with
    | Empty -> -1
    | Node(_,left,right) -> 1 + max (btree_height left) (btree_height right)
;;
