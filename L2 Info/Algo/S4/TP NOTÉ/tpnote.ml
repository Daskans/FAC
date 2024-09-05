(* NOM: BALAVOINE *)
(* PRENOM:  Kyrian *)
(* GROUPE: INF401A4 *)


type rental = int * int * string

type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

type rentals = rental btree

let last_day = 365

 (* EX 1.1 *)
let days (rent: rental) =
    match rent with
    | (ds, de, s) -> ds, de
;;

    


let overlap rent rent' =
    match rent, rent' with
    | (ds1, de1, s), (ds2, de2, s2) -> if ds1 > ds2 && ds1 < de2 then
                                            true
                                        else
                                            false
                                        ;;


 (* EX 1.2 *)
(* insertion si disjoint *)
let rec rentals_insert (rent: rental) t  =
    match t,rent with
    | Empty, rent -> Node(rent,Empty,Empty)
    | Node((ds, de, s), l, Empty), (rent_ds, rent_de, _) -> if overlap rent (ds, de, s) then
                                                                    Node((ds, de, s),l,Empty)
                                                                else if ds > rent_ds then
                                                                    rentals_insert rent l
                                                                else
                                                                    Node((ds, de, s),l,Node(rent,Empty,Empty))
    | Node((ds, de, s), Empty, r), (rent_ds, rent_de, _) -> if overlap rent (ds, de, s) then
                                                                    Node((ds, de, s),Empty,r)
                                                                else if ds > rent_ds then
                                                                    Node((ds, de, s),Node(rent,Empty,Empty),r)
                                                                else
                                                                    rentals_insert rent r
    | Node((ds, de, s), l, r), (rent_ds, rent_de, _) -> if overlap rent (ds, de, s) then
                                                                Node((ds, de, s),l,r)
                                                            else if ds < rent_ds then
                                                                rentals_insert rent r
                                                            else
                                                                rentals_insert rent l
;;


let rec rentals_from_list l =
    match l with
    | head::tail -> rentals_from_list tail
;;  


let r1 = (20,34,"alain");;
let r2= (217, 220, "vasseur");;
let r3= (39,46, "benois");;
let r4= (125,130,"lari");;
let r5= (68,82,"dalle");;
let r6= (147,163, "moret");;
let r7= (260, 275, "faure");;

(* test d'insertion
let rents2025 = rentals_from_list [ r4; r1; r7; r2; r3 ; r5; r6 ];;
 *)

let rents2025 = Node ((147, 163, "moret"),
Node ((68, 82, "dalle"),
Node ((39, 46, "benois"), Node ((20, 34, "alain"), Empty, Empty), Empty),
Node ((125, 130, "lari"), Empty, Empty)),
Node ((217, 220, "vasseur"), Empty,
Node ((260, 275, "faure"), Empty, Empty)))
;;
 (* EX 1.3 *)
(* nombre de jours réservés *)

let rec rentals_nb_days t =
    match t with
    | Empty -> 0
    | Node((ds, de, s), l, r) -> (de - (ds - 1)) + rentals_nb_days l + rentals_nb_days r
;;


(* EX 1.4 *)
let rec rentals_last_day t =
    match t with
    | Empty -> 0
    | Node((ds, de, s), Empty, Empty) -> de
    | Node(h, l, Empty) -> rentals_last_day l
    | Node(h, l, r) -> rentals_last_day r
;;

(* EX 1.5 *)
(* teste si le jour x est réservé - 
   complexité en 0(h) pour t hauteur h *)
let rec rentals_is_free t j =
    match t with
    | Empty -> true
    | Node((ds, de, s), Empty, r) -> if j >= ds && j <= de then
                                    false
                                else if j < ds then
                                    true
                                else
                                    rentals_is_free r j
    | Node((ds, de, s), l, Empty) -> if j >= ds && j <= de then
                                    false
                                else if j < ds then
                                    rentals_is_free l j
                                else
                                        true
    | Node((ds, de, s), l, r) -> if j >= ds && j <= de then
                                    false
                                else if j < ds then
                                    rentals_is_free l j
                                else
                                    rentals_is_free r j
;;

(* EX 1.6 *)
(* nombre maximum de jours où l'appartement est disponible à partir du jour j inclus *)
let rec rentals_max_free t  j = failwith "Code à écrire"


(* EX 1.7 *)
(* demande réservation à partir d'une liste de dates proposées
retourne la date qui permet de réserver l'intervalle le plus grand *)
let  rentals_select t l = failwith "Code à écrire"


(* EX 1.8 *)
(* indiquer votre réponse en commentaires *)
(* ... *)
