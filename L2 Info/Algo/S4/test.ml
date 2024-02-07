(*ceci est un test de OCaml*)
let rec paireOuImpaire n =
  match n with
  | _ when n mod 2 = 0 -> "paire"
  | _ -> "impaire"
;;

let resultats = [
  paireOuImpaire 0;
  paireOuImpaire 5;
]

let () = List.iter (fun res -> Printf.printf "Paire ou impaire : %s\n" res) resultats ;;