type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

type direction = L | R ;;

type binheap = Heap of int btree * int ;;

let tree = Node(9203, Empty, Empty) ;; 

let tree2 = Node(1, Node(2, Node(3, Empty, Empty), Node(3, Empty, Empty)), Node(2, Node(3, Empty, Empty), Node(3, Empty, Empty))) ;;

let heap = Heap(tree2, 7) ;;


let get_dirlist n =
    let rec aux n l =
    if n <= 1 then
        l
    else if n mod 2 = 0 then
        aux (n / 2) (L :: l)
    else
        aux ((n - 1) / 2) (R :: l)
    in
    aux n []
;;

let switch_left t =
    match t with
    | Node(h, Node(h2,l2,r2),r) ->
        if h>h2
            then Node(h2,Node(h,l2,r2),r)
        else t
    | _ -> t
;;

let switch_right t =
    match t with
    | Node(h,l,Node(h2,l2,r2)) ->
        if h>h2
            then Node(h2,l,Node(h,l2,r2))
        else t
    | _ -> t
;;


let rec bubble_up  t l =
    match t,l with
    | Node(e,Empty,Empty), [] -> Node(e,Empty,Empty)
    | Node(x,l,r), d::rest -> if d = L then 
                                let nt = bubble_up l rest in 
                                let t = Node(x, nt, r) in switch_left t
                            else
                                let rt = bubble_up r rest in 
                                let t = Node(x, l, rt) in switch_right t
    | _ -> t
;;

let rec insert x tree list = 
    match (tree, list) with
    | Empty, [] -> Node(x, Empty, Empty)
    | Node(h, l, r), L::q -> Node(h, insert x l q, r)
    | Node(h, l, r), R::q -> Node(h, l, insert x r q)
    |_ -> failwith "NON !"
;;

let heap_insert : int -> binheap -> binheap = fun k h -> match h with
    | Heap(t,n) -> let l = get_dirlist (n+1) in Heap(bubble_up (insert k t l) l,n+1)
;;

let test k h =
    match h with
    | Heap(t,n) -> let l = get_dirlist (n+1) in bubble_up t l
;;