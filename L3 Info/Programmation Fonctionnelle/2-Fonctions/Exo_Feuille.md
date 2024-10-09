# TP 2

## Exercice 1

*1. Écrire une fonction test qui prend en arguments trois entiers x , y , z et retourne true si z est la somme de x et y , et false sinon.*

```ml
let test x y z =
    if z = x + y then true
    else false
;;
```

## Exercice 2

*Écrire une fonction valeur_p4 qui prend en argument un entier x et retourne 3x^4 + 7x − 1.*

```ml
let valeur_p4 x =
    (3*(x*x*x*x)) + (7*x) - 1
;;
```

## Exercice 12

*On considère la suite récurrente d’ordre 2 suivante :*
*u0 = 0*
*u1 = 3*
*un = −un−1 + 2un−2, ∀n >= 2*

*1. Écrire une fonction récursive seq_aux de type int -> int * int qui à tout entier naturel n associe le couple (un, un+1).*

```ml
let rec seq_aux n =
    if n = 0 then
        (0, 3)
    else if n = 1 then
        (3,-9)
    else
        (-(fst(seq_aux (n-1))) + (2*(fst(seq_aux (n-2)))), -(snd(seq_aux (n-1))) + (2*(fst(seq_aux (n-2)))))
;;
```

*2. En déduire une fonction seq qui à tout entier naturel n associe un.*

```ml
let seq n =
    fst(seq_aux n)
;;
```

*3. Quel est le type de seq ?*

int -> int

*4. Quelle est la complexité de seq en fonction de son paramètre n ?*

O(n²)

## Exercice 13

```ml
let epsilon  = 1e-06 ;;
```

```ml
let derivee f h x =
    (f(x +. h) -. f(x -. h)) /. (2. *. h)
;;
```

```ml
let rec derivee_n n f h x = 
    if n = 0 then
        f(x)
    else
        derivee (derivee_n (n-1) f h) h x
;;
```