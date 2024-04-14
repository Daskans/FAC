type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

let tree = Node(8,Node(6,Node(7,Empty,Empty),Node(999,Node(5,Node(2,Empty,Empty),Empty),Node(8,Empty,Empty))),Node(16,Node(12,Empty,Empty),Empty));;

let avl_t = Node((3,2),Node((2,1),Node((1,0),Empty,Empty),Empty),Node((4,1),Empty,Node((5,0),Empty,Empty)));;

let get_height t =
    match t with
    | Empty -> -1
    | Node((h,c),l,r) -> c
;;

let rec calc_height t =
    match t with
    | Empty -> -1
    | Node(h,Empty,Empty) -> 0
    | Node(h,l,r) -> 1 + max (calc_height l) (calc_height r)
;;

let rec tag_bt t = 
    match t with
    | Empty -> Empty
    | Node(h,l,r) -> Node((h,calc_height t),tag_bt l,tag_bt r)
;;

let tag_node c l r =
    Node(c,l,r)
;;

let rec is_avl_aux t =
    match t with
    | Empty -> true
    | Node(h,l,r) -> if get_height l - get_height r > 1 || get_height l - get_height r < -1 then
                        false
                    else
                        is_avl_aux l && is_avl_aux r
;;

let is_avl t =
    is_avl_aux t
;;

let rec rotate_aux t = 
    match t with
    | Empty -> Empty
    | Node((h,n),l,r) -> Node((h,calc_height t),rotate_aux l,rotate_aux r)
;;

let l_rotate t  = 
    match t with
    | Empty -> failwith "tree not suitable for left rotation"
    | Node(h,l,Empty) -> Node(h,l,Empty)
    | Node((h,n),l,Node((h2,n2),l2,r2)) -> rotate_aux (Node((h2,n2+1),Node((h,n-1),l,l2),r2))
;;

let lr_rotate t  = 
    match t with
    | Empty -> failwith "tree not suitable for left rotation"
    | Node(h,Empty,l) -> failwith "tree not suitable for left rotation"
    | Node(h,Node(h2,r,Empty),l) -> failwith "tree not suitable for left rotation"
    | Node((h,n),Node((h2,n2),l2,Node((h3,n3),l3,r3)),r) -> rotate_aux (Node((h3,n3),Node((h2,n2),l2,l3),Node((h,n),r3,r)))
;;

