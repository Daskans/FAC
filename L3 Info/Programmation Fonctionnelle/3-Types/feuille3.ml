(* EXERCICE 1 *)

(* int * int *)

(* EXERCICE 2 *)

(* ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b = <fun> *)

(* EXERCICE 3 *)

let rec fib_aux u n = 
    match u, n with
    | _, 0 -> failwith "ERROR : no 0th value in Fibonacci"
    | (u1, u2), n -> if n = 1 || n = 2 then
                        u1
                    else if n = 3 then 
                        u1 + u2 
                    else 
                        fib_aux (u2, (u1 + u2)) (n-1)
;;


let fib n =
    fib_aux (1,1) n
;;

(* EXERcICE 4 *)

(* 'x', 2.1, (true, 0)              -> char * float * (bool * int) *)
(* 3 + 2, false || 2 = 3, "bonjour" -> int * bool * string *)
(* let p = 1, 2 in snd p, fst p     -> int * int *)

(* EXERCICE 5 *)

(* int * bool * string     -> 8, true, "abc" *)
(* (int * bool) * string   -> (8, true), "abc" *)
(* int * (bool * string)   -> 8, (true, "abc") *)

(* EXERCICE 6 *)

type couleur = Pique | Coeur | Carreau | Trefle;;

type carte =
    As of couleur
    | Roi of couleur
    | Dame of couleur
    | Valet of couleur
    | Numero of int * couleur
;;

let couleur_carte carte =
    match carte with
    | Numero(_, couleur) -> couleur
    | As(couleur) | Roi(couleur) | Dame(couleur) | Valet(couleur) -> couleur
;;

let est_de_couleur carte couleur =
    if couleur_carte carte = couleur then
        true
    else 
        false
;;

let est_de_figure carte =
    match carte with
    | Numero(_) -> false
    | _ -> true
;;

(* EXERCICE 7 *)

type carburant = Diesel | Essence | Electrique ;;

type vehicule = Vehicule of carburant * int ;;

let make_vehicle fuel nb_wheel =
    Vehicule(fuel, nb_wheel)
;;

let carburant_of vehicle =
    match vehicle with
    |Vehicule(fuel,_) -> fuel
;;

let nb_wheel_of vehicle =
    match vehicle with
    |Vehicule(_,nb_wheel) -> nb_wheel
;;

let can_run vehicle =
    if carburant_of vehicle = Diesel && nb_wheel_of vehicle >= 4 then
        false
    else
        true
;;

let consommation vehicle kilometers =
    if carburant_of vehicle = Diesel then
        ((6. /. 100.) *. kilometers) *. 1.5
    else if carburant_of vehicle = Essence then
        ((8. /. 100.) *. kilometers) *. 1.5
    else 
        ((10. /. 100.) *. kilometers) *. 0.25
;;

(* EXERCICE 8 *)

type expr =
    Var of string
    | Number of float
    | Plus of expr * expr
    | Minus of expr * expr
    | Mult of expr * expr
    | Exp of expr
;;

let vx = Var("x") ;;
let vy = Var("y") ;;

let e1 = Plus(Mult(Number 2., Var "x"), Number 1.) ;;

let e2 = Plus(Mult(Number 3., Mult(Var "x", Var "x")), Plus(Mult(Number 2., Var "x"), Number 1.)) ;;

let rec derivee var expr =
    match var, expr with
    | Var(x), Var(x1) -> if x = x1 then
                            Number(1.)
                        else
                            Number(0.)
    | Var(x), Number(_) -> Number(0.)
    | Var(x), Plus(e1, e2) -> Plus(derivee var e1, derivee var e2)
    | Var(x), Minus(e1, e2) -> Minus(derivee var e1, derivee var e2)
    | Var(x), Mult(e1, e2) -> Plus(Mult( e1, derivee var e2),Mult(derivee var e1, e2))
    | Var(x), Exp(e) -> Mult(derivee var e,Exp(e))
    | _, _ -> failwith "cas non calculé"
;;

let rec derivee_n var expr n =
    if n = 1 then
        derivee var expr
    else if n > 1 then
        derivee_n var (derivee var expr) (n-1)
    else 
        Var("ERROR")
;;