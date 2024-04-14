type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

let tree = Node(8,Node(6,Node(7,Empty,Empty),Node(999,Node(5,Node(2,Empty,Empty),Empty),Node(8,Empty,Empty))),Node(16,Node(12,Empty,Empty),Empty));;

let avl_t = Node((3,2),Node((2,1),Node((1,0),Empty,Empty),Empty),Node((4,1),Empty,Node((5,0),Empty,Empty)));;

let avl_t2 = Node((4,2),Node((2,1),Node((1,0),Empty,Empty),Node((3,0),Empty,Empty)),Node((7,1),Empty,Empty));;

let rec calc_height t =
  match t with
  | Empty -> -1
  | Node(h,Empty,Empty) -> 0
  | Node(h,l,r) -> 1 + max (calc_height l) (calc_height r)
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

let r_rotate t  = 
  match t with
  | Empty -> failwith "tree not suitable for left rotation"
  | Node(h,Empty,r) -> Node(h,Empty,r)
  | Node((h,n),Node((h2,n2),l2,r2),r) -> rotate_aux (Node((h2,n2+1),l2,Node((h,n-1),r2,r)))
;;

let lr_rotate t  = 
  match t with
  | Empty -> failwith "tree not suitable for left rotation"
  | Node(h,Empty,r) -> failwith "tree not suitable for left rotation"
  | Node(h,Node(h2,l,Empty),r) -> failwith "tree not suitable for left rotation"
  | Node(h,l,r) -> r_rotate (Node(h,(l_rotate l),r))
;;

let rl_rotate t  = 
  match t with
  | Empty -> failwith "tree not suitable for left rotation"
  | Node(h,l,Empty) -> failwith "tree not suitable for left rotation"
  | Node(h,l,Node(h2,Empty,r)) -> failwith "tree not suitable for left rotation"
  | Node(h,l,r) -> l_rotate (Node(h,l,(r_rotate r)))
;;

