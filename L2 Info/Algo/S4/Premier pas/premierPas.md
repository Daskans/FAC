# Premier pas en OCaml

## I) Introduction à OCaml

### 1) Les expressions

Utiliser utop dans le terminal pour les exercices suivants

#### Exercice 1

**Déterminer sur feuille le type et la valeur des expressions suivantes, puis tester vos réponses :**

`45 + 2*(27-11);;`
`- : int = 77`

`25/4 + 2*9 + (int_of_char 'A');;`
`- : int = 89`

`2e3 +. 2.5 *. (float_of_int 4);;`
`- : float = 2010`

`6 / 3*2;;`
`- : int = 4`

#### Exercice 2

**Déterminer sur feuille le type et la valeur des expressions suivantes, puis tester vos réponses, sachant que mod désigne l’opérateur ”modulo”.**

`min 22 56 > 2*7;;`
`- : bool = true` *pourquoi ?*

`not (6 / 3*2 = 1 || 4 * 3/2 = 5);;`
`- : bool = true`

`int_of_float(3.14 *. 2.) = 6;;`
`- : bool = true`

`(11+13) mod 2 = 0 && 2*7 + 1 mod 2 = 1;;`
`- : bool = true` *pourquoi ?*

### 2) Les liaisons

#### Exercice 3

**déterminer la valeur des expressions**
`let x = 5.0 in x *. x +. 30.0;;`
`- : float = 55.`

`let x = 5 in let y = x+2 in x+3*y;;`
`- : int = 26`

`let x = 14 in let y = x > 0 in y && x < 30;;`
`- : bool = true`

### 3) Les fonctions

#### Exercice 4

**déterminer la valeur de l’expression**
`let f = fun x y -> x - y in f (f 1 2) 3;;`
`- : int = -4`

`let cube x = x * x * x in (cube 2) + (cube 3);;`
`- : int = 35`

#### Exercice 5

**Écrire une fonction pythagore a b c qui prend en paramètre trois entiers a, b et c qui teste si a2 + b2 = c2. On écrira d’abord une fonction carre x qui prend en paramètre un entier x et renvoie x2.**
`let carre x = x * x;;`
`let pythagore a b c = carre a + carre b = carre c;;`
`pythagore 3 4 5;;`
`- : bool = true`

#### Exercice 6

**Ecrire une fonction vector_norm x y qui prend en paramètre deux nombres flottants (les coordonnées x et y d’un vecteur) et qui calcule la norme du vecteur, c’est-à-dire la racine carré de x^2 + y^2. La racine carré est une fonction prédéfinie en Ocaml de type sqrt: float -> float .**
`let carre_float x = x *. x;;`
`let vector_norm x y = sqrt (carre_float x +. carre_float y);;`
`vector_norm 2.5 4.5;;`
`- : float = 5.1478150704935`

#### Exercice 7

**Déterminer le type des expressions suivantes**
`fun x y -> x;;`
`- : 'a -> 'b -> 'a = <fun>`

`fun x y -> y;;`
`- : 'a -> 'b -> 'b = <fun>`

`fun f -> fun x -> f (f x);;`
`- : ('a -> 'a) -> 'a -> 'a = <fun>`

`fun f g -> fun x -> f (g x);;`
`- : ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b = <fun>`

#### Exercice 8
**Indiquez ce qui est calculé par l’expression suivante.**
`let square = fun x -> x * x in let compose = fun f g -> fun x -> f (g x) in compose square square;;`
`- : int -> int = <fun>`
#### Exercice 9
**Écrire une fonction diff_between a b f qui prend en paramètre deux entiers a et b et une fonctions f de type int -> int et qui retourne la différence entre la valeur de f en b et la valeur de f en a.**
`let diff_between a b f = f b - f a;;`
`diff_between 2 4 carre;;`
`- : int = 12`
### 4) Conditions et filtrage
**condition if:**
if [...] then
    [...]
else
    [...]
**ou plus simplement**
if [...] then [...] else [...]
#### Exercice 10
**Déterminer le type des expressions suivantes**
`fun x y -> if x = y then x else y;;`
`- : 'a -> 'a -> 'a = <fun>`

`fun x y z -> if x = y then x else z;;`
`- : 'a -> 'a -> 'a -> 'a = <fun>`

`fun x y z -> if x = y then 0 else z;;`
`- : 'a -> 'a -> int -> int = <fun>`
#### Exercice 11
**Ecrire une fonction museum_price: int -> float qui prend en paramètre un age (de type entier) et renvoie le prix d’entrer au musée en fonction de l’age. Ce prix est 6 euros si l’age est inférieur ou égale à 11 ans, 9 euros si l’age est compris entre 12 ans et 18 ans (compris), et 15 euros si l’age est strictement supérieur à 18 ans.**
`let museum_price age = if age <= 11 then 6 else if age <= 18 then 9 else 15;;`
#### Exercice 12
**Ecrire une fonction helloworld qui prend en paramètre une chaine de charactère indiquant une langue et renvoie ”Bonjour” écrit dans cette langue. Cette fonction traitera le cas de plusieurs langues différentes. Si la langue passée en paramètre ne fait pas partie des cas prévus, la fonction renverra ”Je ne parle pas” concaténé avec la langue demandée.**
let helloworld language =
    match language with
    | "français" -> "bonjour"
    | "anglais" -> "hello"
    | "espagnole" -> hola"
    | "japonais" -> "ohayou"
    | _ -> "Je ne parle pas "
;;