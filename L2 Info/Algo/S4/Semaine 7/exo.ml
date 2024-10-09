type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

type direction = L | R ;;

let tree = Node(4, Node(2, Node(1, Empty, Empty), Node(3, Empty, Empty)), Node(6, Node(5, Empty, Empty), Node(7, Empty, Empty)) ) ;;

let rec follow_path t l =
    match t, l with
    | Empty, _ -> -1
    | Node(h,_,_), [] -> h
    | Node(_,left,right), head::tail -> if head = L then 
                                            follow_path left tail 
                                        else if head = R then 
                                            follow_path right tail
                                        else
                                            failwith "follow_path"
;;

let rec path_to_key  t x = 
    match t with
    | Empty -> []
    | Node(h,l,r) -> if h = x then []
                     else if x > h then [R]@(path_to_key r x)
                     else [L]@(path_to_key l x)
;;