type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

let tree = Node(8,Node(6,Node(7,Empty,Empty),Node(999,Node(5,Node(2,Empty,Empty),Empty),Node(8,Empty,Empty))),Node(16,Node(12,Empty,Empty),Empty));;

let tree2 = Node (22, Node (72, Empty, Empty), Empty);;

(*Exercice 1*)

let rec btree_mult2_leaves t =
    match t with
    | Empty -> t
    | Node(h,Empty,Empty) -> Node(h*2,Empty,Empty)
    | Node(h,l,r) -> Node(h,btree_mult2_leaves l,btree_mult2_leaves r)
;;

(*Exercice 2*)

let rec btree_expand_leaves btree =
    match btree with
    | Empty -> btree
    | Node(h,Empty,Empty) -> Node(h,Node(h*2,Empty,Empty),Node(1+h*2,Empty,Empty))
    | Node(h,l,r) -> Node(h,btree_expand_leaves l,btree_expand_leaves r)
;;

(*Exercice 3*)

let rec btree_map f btree =
    match btree with
    | Empty -> Empty
    | Node(h,l,r) -> Node(f h,btree_map f l,btree_map f r)
;;

(*Exercice 4*)

let rec btree_perfect h =
    let rec aux n h =
        if h = -1 then
            Empty
        else
            Node(n, aux(2*n) (h-1), aux(1+2*n) (h-1))
        in aux 1 h
;;