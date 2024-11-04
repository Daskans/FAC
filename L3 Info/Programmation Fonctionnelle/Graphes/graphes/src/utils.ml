(** new list containing the values of l in the same order 
    except the ones that satisfy the predicate pred *)
let remove_if pred l = List.filter (fun x -> not (pred x)) l

(** new list containing the values of l in the same order 
    that satisfy the predicate pred *)
let remove_if_not pred l = List.filter pred l

(** predicate for parity of an integer *)
let even_p n = n mod 2 = 0

(** true if every element of l satisfies pred *)
let every pred l = List.fold_right (fun x y -> pred x && y) l true

(** true if no element of l satisfies pred *)
let none pred l = every (fun b -> not (pred b)) l

(** true if at least one element of l satisfies pred *)
let rec some pred l =
  match l with
    [] -> false
   | e :: tl -> pred e || some pred tl 

(** premier élément d'une liste *)
let first_elt l = List.hd l

(** dernier élément d'une liste *)
let last_elt l = List.nth l (pred (List.length l))

(** concatenation of list images of the elements of L *)
let mapcan f l =  List.concat (List.map f l)
