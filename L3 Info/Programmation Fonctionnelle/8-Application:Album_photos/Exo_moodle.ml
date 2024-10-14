let list = [(1,2); (5,3); (2,3); (5,1)]

let couples_elements l =
    let rec aux l new_l =
        match l with
        | [] -> new_l
        | (x,y)::tail -> if not (is_in_list x new_l) then
                            if is_in_list y new_l then
                                aux tail (x::new_l)
                            else
                                if x != y then
                                    aux tail (x::(y::new_l))
                                else 
                                    aux tail (x::new_l)
                        else if is_in_list x new_l && not (is_in_list y new_l) then
                            aux tail (y::new_l)
                        else aux tail new_l
    in aux l []
;;

                        


let rec is_in_list x list =
    match list with
    | [] -> false
    | head::tail -> if head = x then true else false || is_in_list x tail
;;