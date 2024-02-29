type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

let tree = Node (22, Node (72, Empty, Empty), Empty);;

let tree2 = Node (22, Node (72, Empty, Empty), Node (23, Empty, Empty));;


let tree3 = Node (33, 
                Node (3, 
                    Node (28, 
                        Node (25, 
                            Empty, 
                            Empty), 
                        Empty), 
                    Empty), 
                Node (90, 
                    Node (10, 
                        Empty, 
                        Node (11, 
                            Empty, 
                            Empty)
                        ), 
                    Empty)
                )
            ;;

let rec btree_is_full t = 
    match t with
    | Empty -> true
    | Node(_,Empty,Empty) ->true
    | Node(_,Empty,_) -> false
    | Node(_,_,Empty) -> false
    | Node(head,left,right) -> btree_is_full left && btree_is_full right
;;

let rec btree_is_perfect t =
    let rec aux t =
        match t with
        | Empty -> 0
        | Node(head,left,right) -> 1 + aux left + aux right
    in
    match t with
    | Empty -> true
    | Node(_,Empty,Empty) ->true
    | Node(_,Empty,_) -> false
    | Node(_,_,Empty) -> false
    | Node(_,left,right) -> if (aux left = aux right) && (btree_is_perfect left && btree_is_perfect right)then true else false
;;
    
