(*On définit le type region comme suit:
type region = Medoc | Graves | Alsace | Beaujolais | Touraine | Bourgogne

    1) Écrire un type couleur ayant trois valeurs: Blanc, Rouge et Rose.
    2) En utilisant les types region et couleur, définir un type vin permettant de représenter un vin par un triplet contenant dans l'ordre, sa région, sa couleur et son millésime (c'est-à-dire, une année, de type int).
    3) Écrire les accesseurs
        region_of vine,
        color_of vine,
        year_of vine
    qui permettent de récupérer respectivement la région, la couleur et le millésime du vin vine.
    4) Écrire un prédicat bordeaux_p vine qui retourne vrai si le vin vine est un Bordeaux (Médoc ou Graves).
    5) Écrire un prédicat has_color_p vine color qui retourne vrai si la couleur du vin vine est color
    6) Écrire un prédicat after_year_p vine year qui retourne vrai si le millésime du vin vine est supérieur ou égal à year.
*)

type region = Medoc | Graves | Alsace | Beaujolais | Touraine | Bourgogne ;;

type couleur = Rouge | Blanc | Rose ;;

type vine = Vine of region * couleur * int ;;

let vine1 = Vine(Medoc, Rouge, 1980) ;;
let vine2 = Vine(Beaujolais, Blanc, 2006) ;;

let region_of vine =
    match vine with
    | Vine(region,_,_) -> region
;;

let color_of vine = 
    match vine with
    | Vine(_,couleur,_) -> couleur
;;

let year_of vine = 
    match vine with
    | Vine(_,_,annee) -> annee
;;

let bordeaux_p vine =
    if region_of vine = Medoc || region_of vine = Graves then
        true
    else
        false
;;

let has_color_p vine color =
    if color_of vine = color then
        true
    else
        false
;;

let after_year_p vine year =
    if year_of vine >= year then
        true
    else
        false
;;
