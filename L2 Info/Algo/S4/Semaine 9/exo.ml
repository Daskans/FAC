type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

let tree = Node(1, Node(2, Node(4, Empty, Empty), Node(5, Empty, Empty)), Node(3, Empty, Empty));;

let postfixe_list_of_btree t =
    let rec aux t list = 
        match t with
        | Empty -> list
        | Node(v, l, r) -> aux l (aux r (v::list))
    in aux t []
;;
