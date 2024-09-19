# TP 3

## Exercice 1

*Quel est le type de la fonction fun x y -> (x, y) ?*

int * int

## Exercice 2

*Quel est le type de la fonction compose vue précédemment ?*
*let compose f g = fun x -> f (g x)*

('a -> 'b) -> ('c -> 'a) -> 'c -> 'b = <fun>

## Exercice 3

*On reprend la suite de Fibonacci définie par u0 = 1, u1 = 1 et pour tout n > 2, un = un−1 + un−2.*
*En utilisant une fonction auxiliaire qui calcule le couple (un, un+1), améliorer fib pour que l’appel fib n n’utilise qu’un nombre linéaire de sommes.*

```ml
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
```

## Exercice 4

*Pour chacun des types suivants, donner une expression ayant ce type ainsi que la valeur de l’expression.*

'x', 2.1, (true, 0)                 -> char * float * (bool * int)
3 + 2, false || 2 = 3, "bonjour"    -> int * bool * string
let p = 1, 2 in snd p, fst p        -> int * int

## Exercice 5

*Pour chacun des types suivants, donner une expression ayant ce type ainsi que la valeur de l’expression.*

int * bool * string     -> 8, true, "abc"
(int * bool) * string   -> (8, true), "abc"
int * (bool * string)   -> 8, (true, "abc")

## Exercice 6

*Soient les types couleur et carte définis comme suit :*

```ml
type couleur = Pique | Coeur | Carreau | Trefle

type carte =
    As of couleur
    | Roi of couleur
    | Dame of couleur
    | Valet of couleur
    | Numero of int * couleur
```

*1 Écrire un accesseur couleur_carte carte de type carte -> couleur qui retourne la couleur d’une carte.*

```ml
let couleur_carte carte =
    match carte with
    | Numero(_, couleur) -> couleur
    | As(couleur) | Roi(couleur) | Dame(couleur) | Valet(couleur) -> couleur
;;
```

*2 Écrire un prédicat est_de_couleur carte couleur de type carte -> couleur -> bool qui retourne true si carte est de couleur couleur.*
*On utilisera l’accesseur couleur_carte .*

```ml
let est_de_couleur carte couleur =
    if couleur_carte carte = couleur then
        true
    else 
        false
;;
```

*3 Écrire un prédicat est_une_figure carte de type carte -> bool qui retourne true si carte est une figure, false sinon.*

```ml
let est_de_figure carte =
    match carte with
    | Numero(_) -> false
    | _ -> true
;;
```

## Exercice 7

*1. Définir un type carburant ayant trois constructeurs Diesel , Essence ou Electrique .*

```ml
type carburant = Diesel | Essence | Electrique ;;
```

*2. Un véhicule est caractérisé par son carburant et son nombre de roues. Définir un type vehicule répondant à ces critère*

```ml
type vehicule = Vehicule of carburant * int ;;
```
*3. Écrire le constructeur make_vehicule de type carburant -> int -> vehicule .*

```ml
let make_vehicle fuel nb_wheel =
    Vehicule(fuel, nb_wheel)
;;
```

*4. Écrire les accesseurs carburant_of de type vehicule -> carburant et nb_wheels_of de type*
*vehicule -> int qui retournent respectivement le carburant et le nombre de roues d’un véhicule.*

```ml
let carburant_of vehicle =
    match vehicle with
    |Vehicule(fuel,_) -> fuel
;;

let nb_wheel_of vehicle =
    match vehicle with
    |Vehicule(_,nb_wheel) -> nb_wheel
;;
```

*5. Lors des pics de pollution, les véhicules diesel à 4 roues au moins sont interdits.*
*Écrire une fonction can_run : vehicule -> bool qui teste si un véhicule est autorisé.*

```ml
let can_run vehicle =
    if carburant_of vehicle = Diesel && nb_wheel_of vehicle >= 4 then
        false
    else
        true
;;
```

*6. Pour rouler 100km, un véhicule électrique consomme environ 10kWh, un véhicule diesel consomme environ 6L de carburant, et un véhicule essence consomme environ 8L.*
*Sachant qu’1kWh coûte 0.25 EUR et qu’un litre de carburant coûte 1.5 EUR, écrire une fonction consommation : vehicule -> int -> float*
*telle que consommation v n renvoie le coût d’utilisation du véhicule v sur n kilomètres.*

```ml
let consommation vehicle kilometers =
    if carburant_of vehicle = Diesel then
        ((6. /. 100.) *. kilometers) *. 1.5
    else if carburant_of vehicle = Essence then
        ((8. /. 100.) *. kilometers) *. 1.5
    else 
        ((10. /. 100.) *. kilometers) *. 0.25
;;
```

## Exercice 8

*On représente des expressions arithmétiques utilisant les opérations +, −, ×, exp par le type suivant :*

```ml
type expr =
    Var of string
    | Number of float
    | Plus of expr * expr
    | Minus of expr * expr
    | Mult of expr * expr
    | Exp of expr
;;
```

*Ainsi, une variable x est représentée par l’expression OCaML Var "x" et 3x2 + 2x + 1 par*

*Plus (Mult (Number 3., Mult (Var "x", Var "x")), Plus (Mult (Number 2., Var "x"), Number 1.))*

*1. Définir deux variables vx et vy contenant respectivement des variables x et y.*

```ml
let vx = Var("x") ;;
let vy = Var("y") ;;
```

*2. Définir la variable e1 contenant l’expression 2x + 1.*

```ml
let e1 = Plus(Mult(Number 2., Var "x"), Number 1.) ;;
```

*3. Définir la variable e2 contenant l’expression 3x² + 2x + 1.*

```ml
let e2 = Plus(Mult(Number 3., Mult(Var "x", Var "x")), Plus(Mult(Number 2., Var "x"), Number 1.)) ;;
```

*4. Implémenter une fonction derivee var expr par une traduction directe des cinq règles ci-dessus,*
*i.e. par un simple filtrage avec cinq cas distincts.*

```ml
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
```

*5. Écrire la fonction derivee_n var expr n qui retourne une expression correspondant à la dérivée n-ème de expr .*

```ml
let rec derivee_n var expr n =
    if n = 1 then
        derivee var expr
    else if n > 1 then
        derivee_n var (derivee var expr) (n-1)
    else 
        Var("ERROR")
;;
```
