type 'a btree =
    | Empty
    | Node of 'a * 'a btree * 'a btree
;;

let t1 = (Node(2, 
            Node(4, 
                Node(6, 
                    Node(8, 
                        Empty, 
                        Empty
                    ),
                    Node(10, 
                        Node(12, 
                            Empty, 
                            Empty), 
                        Empty
                    )
                ),
                Node(14, 
                    Empty, 
                    Empty
                )
            ),
            Node(16, 
                Empty, 
                Node(18, 
                    Empty, 
                    Empty
                )
            )
        )
    )
;;

(*Exercices moodle*)

let rec bst_max t = 
    match t with
    | Empty -> failwith "empty"
    | Node(head,_,Empty) -> head
    | Node(_,_,right) -> bst_max right
;;

let rec bst_pop_max t =
    match t with
    | Empty -> failwith "empty"
    | Node(head, left, Empty) -> (left, head)
    | Node(head, left, right) -> 
        let (max, new_right) = bst_pop_max right in
        (Node(head, left, new_right), max)
;;

let rec bst_remove t c =
    match t with
    | Empty -> t


    
