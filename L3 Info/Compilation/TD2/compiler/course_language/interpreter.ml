open Ast
open Abstract_machine

exception Return_exp of value option
exception Non_variable_reference of expr
exception Non_bool_test of expr
exception Non_integer_array_position of expr

let get_tab_pos name pos = name ^ string_of_int pos

(* Sémantique d’une opération binaire*)
let operation_of_binop (op : binop) (v1 : value) (v2 : value) =
    match op, v1, v2 with
    | Add, VInt(v1), VInt(v2) -> VInt (v1 + v2)
    | Add, VFloat(v1), VFloat(v2) -> VFloat (v1 +. v2)
    | Sub, VInt(v1), VInt(v2) -> VInt (v1 - v2)
    | Sub, VFloat(v1), VFloat(v2) -> VFloat (v1 -. v2)
    | Mul, VInt(v1), VInt(v2) -> VInt (v1 * v2)
    | Mul, VFloat(v1), VFloat(v2) -> VFloat (v1 *. v2)
    | Div, VInt(v1), VInt(v2) -> VInt (v1 / v2)
    | Div, VFloat(v1), VFloat(v2) -> VFloat (v1 /. v2)
    | Mod, VInt(v1), VInt(v2) -> VInt (v1 mod v2)
    | And, VBool(v1), VBool(v2) -> VBool (v1 && v2)
    | Or, VBool(v1), VBool(v2) -> VBool (v1 || v2)
    | Eq, VInt(v1), VInt(v2) -> VBool (v1 = v2)
    | Eq, VFloat(v1), VFloat(v2) -> VBool (v1 = v2)
    | Eq, VBool(v1), VBool(v2) -> VBool (v1 = v2)
    | Neq, VInt(v1), VInt(v2) -> VBool (v1 <> v2)
    | Neq, VFloat(v1), VFloat(v2) -> VBool (v1 <> v2)
    | Neq, VBool(v1), VBool(v2) -> VBool (v1 <> v2)
    | Lt, VInt(v1), VInt(v2) -> VBool (v1 < v2)
    | Lt, VFloat(v1), VFloat(v2) -> VBool (v1 < v2)
    | Lt, VInt(v1), VFloat(v2) -> VBool (float_of_int v1 < v2)
    | Lt, VFloat(v1), VInt(v2) -> VBool (v1 < float_of_int v2)
    | Lt, VBool(v1), VBool(v2) -> VBool (v1 < v2)
    | Gt, VInt(v1), VInt(v2) -> VBool (v1 > v2)
    | Gt, VFloat(v1), VFloat(v2) -> VBool (v1 > v2)
    | Gt, VInt(v1), VFloat(v2) -> VBool (float_of_int v1 > v2)
    | Gt, VFloat(v1), VInt(v2) -> VBool (v1 > float_of_int v2)
    | Gt, VBool(v1), VBool(v2) -> VBool (v1 > v2)
    | Leq, VInt(v1), VInt(v2) -> VBool (v1 <= v2)
    | Leq, VFloat(v1), VFloat(v2) -> VBool (v1 <= v2)
    | Leq, VInt(v1), VFloat(v2) -> VBool (float_of_int v1 <= v2)
    | Leq, VFloat(v1), VInt(v2) -> VBool (v1 <= float_of_int v2)
    | Leq, VBool(v1), VBool(v2) -> VBool (v1 <= v2)
    | Geq, VInt(v1), VInt(v2) -> VBool (v1 >= v2)
    | Geq, VFloat(v1), VFloat(v2) -> VBool (v1 >= v2)
    | Geq, VInt(v1), VFloat(v2) -> VBool (float_of_int v1 >= v2)
    | Geq, VFloat(v1), VInt(v2) -> VBool (v1 >= float_of_int v2)
    | Geq, VBool(v1), VBool(v2) -> VBool (v1 >= v2)
    | _ -> failwith ("ERROR : unsupported binop operation : "
             ^ string_of_binop op)

(* Sémantique d’une opération unaire*)
let operation_of_unop (op : unop) (v : value) =
    match op, v with
    | UMin, VInt v -> VInt (-v)
    | UMin, VFloat v -> VFloat (-.v)
    | Not, VBool v -> VBool (not v)
    | _ -> failwith "ERROR : unsupported unop operation"

(* Cette fonction interprète une expression et renvoie sa valeur. 
Vous devez traiter tous les cas possibles (cf module Ast). 
Reportez-vous au cours pour une explication de la sémantique. 
On conseille de traiter parallèlement expressions et 
instructions par ordre de complexité (décrit dans le cours). 
Vous pouvez laisser des cas non-traités simplement en leur associant 
[failwith "todo"] qui fera planter le programme sur ces cas, 
mais permettra de compiler et de traiter les autres.*)
let rec interpret_expr (map : value Util.Environment.t)
    (map_function : (Ast.argument list * Ast.instruction) Util.Environment.t)
    (expr : Ast.expr) =
    match expr with
    | Cst_i(v, _) -> VInt v
    | Cst_f(v, _) -> VFloat v
    | Cst_b(v, _) -> VBool v
    | Var(name, _) ->
        let value = Util.Environment.get map name in
        (match value with
        | Some v -> v
        | None -> failwith ("ERROR : variable " ^ name ^ " not found"))

    | Binop(op, e1, e2, _) ->
        let v1 = interpret_expr map map_function e1 in
        let v2 = interpret_expr map map_function e2 in
        operation_of_binop op v1 v2

    | Unop(op, e, _) -> operation_of_unop op (interpret_expr map map_function e)
    
    | Array_val(name, e, _) ->
        let index = match interpret_expr map map_function e with
        | VInt x -> x
        | _ -> failwith "index not an integer"
        in
        let tab = Util.Environment.get map name in
        (match tab with
        | Some(VArray(array_name, env)) ->
            (match Util.Environment.get env 
            (array_name ^ (string_of_int index)) with
            | Some v -> v
            | _ -> failwith ("ERROR : array " ^ name ^ " not found"))
        | None -> failwith ("ERROR : array " ^ name ^ " is undefined")
        | _ -> failwith ("ERROR : not an array in Array_val"))

    | Size_tab(name, _) ->
        let tab = Util.Environment.get map name in
        (match tab with
        | Some(VArray(array_name, _)) ->
            Option.get (Util.Environment.get map (array_name ^ "size"))
        | _ -> failwith ("ERROR : not an array : " ^ name))

    | Func(name, args, _) ->
        let params, body =
            match Util.Environment.get map_function name with
            | Some (params, body) -> (params, body)
            | _ -> failwith ("ERROR : function " ^ name ^ " not found")
        in
        let func_core = Util.Environment.new_environment () in
        List.iter2 ( 
            fun (_, _, param_name) expr -> 
                let value = interpret_expr map map_function expr in
                Util.Environment.modify func_core param_name value) params args;
        let run =
            try interpret_instruction func_core map_function body; None
            with Return_exp v -> v in
            match run with
            | Some v -> v
            | None -> failwith "ntm"

    | _ -> failwith "ERROR : unsupported expr operation"

(* Cette fonction interprète une instruction. Le «and» est là pour qu’elle 
soit co-récursive avec interpret_expr (à cause des appels de fonctions). 
Elle ne renvoie rien, mais applique directement des effets de bord sur [map]. 
Reportez-vous au cours pour la sémantique.*)
and interpret_instruction (map : value Util.Environment.t)
    (map_function : (Ast.argument list * Ast.instruction) Util.Environment.t)
    (instruction : Ast.instruction) =
    match instruction with
    | Affect(name, expr, _) ->
        let value = interpret_expr map map_function expr in
        Util.Environment.modify map name value

    | Block(instructions, _) -> List.iter (interpret_instruction map 
                                map_function) instructions

    | IfThenElse(expr, thenInstruction, elseInstruction, _) ->
        let value = interpret_expr map map_function expr in
        (match value with
        | VBool true -> interpret_instruction map map_function thenInstruction
        | VBool false -> interpret_instruction map map_function elseInstruction
        | _ -> failwith "ERROR : non-bool test")

    | While(expr, instruction, _) ->
        let rec loop expr instruction =
            let value = interpret_expr map map_function expr in
            (match value with
            | VBool true -> interpret_instruction map map_function instruction;
                            loop expr instruction
            | VBool false -> ()
            | _ -> failwith "ERROR : non-bool test")
        in loop expr instruction

    | Affect_array (name, i_expr, v_expr, _) ->
        let value = interpret_expr map map_function v_expr
        and index =
            match interpret_expr map map_function i_expr with
            | VInt i -> i
            | _ -> failwith "ERROR : array index not an integer"
        in let tab = Util.Environment.get map name in
        (match tab with
        | Some(VArray(array_name, _)) ->
            (Util.Environment.modify map (get_tab_pos array_name index) value)
        | _ -> failwith ("ERROR : not an array : " ^ name))

    | Array_decl (_, array_name, expr, _) ->
        let size =
            match interpret_expr map map_function expr with
            | VInt x -> x
            | _ -> failwith "ERROR : array size not an integer"
        in
        Util.Environment.modify map array_name (VArray (array_name ^ "#", map));
        Util.Environment.modify map (array_name ^ "#size") (VInt size)

    | Proc(name, expr, _) ->
        let value = interpret_expr map map_function expr in
        (match name with
        | "return" -> raise (Return_exp (Some value))
        | _ -> failwith "ERROR : unsupported proc operation")

    | Print_str(str, _) -> print_string str
    
    | Print_expr(expr, _) -> print_string (string_of_value 
                            (interpret_expr map map_function expr))
    
    | Var_decl(basic, name, _) ->
        let value = match basic with
        | TInt -> VInt 0
        | TFloat -> VFloat 0.
        | TBool -> VBool false
        | TNull -> VNone
        in Util.Environment.modify map name value

    | _ -> failwith ("ERROR : unsupported instruction operation")

(*Cette fonction doit interpréter une déclaration de fonction. 
Elle consiste simplement à associer la liste des arguments et 
le corps de la fonction à son nom dans l’environnement [functions].*)
let interpret_func_decl
    (functions : (Ast.argument list * Ast.instruction) Util.Environment.t)
    (func_decl : Ast.function_decl) =
    ignore (functions, func_decl);
    () (*à compléter*)

(* Cette fonction utilitaire vous est fournie : elle permet de mettre la 
liste des arguments à la même taille que celle des paramètres de la 
fonction main : s’il y en a pas assez, on leur attribue la valeu VNone, 
s’il y en a trop, on ignore les derniers. Cela permet de rendre la ligne 
de commande un peu plus résiliente à un mauvais nombre d’argument sur 
l’exécution d’un programme *)
let normalize_arg_list args vars =
    if List.length args < List.length vars then
        args @ List.init (List.length vars - List.length args) (fun _ -> "")
    else if List.length args > List.length vars then
        List.filteri (fun i _ -> i < List.length vars) args
    else args

(* Cette fonction permet d’exécuter une liste de déclaration de fonctions 
sur les arguments passés à la ligne de commande, 
et lance dessus la fonction main. Elle analyse la liste des fonctions, 
et stocke leurs définitions dans un environnement de fonctions, 
puis récupère la définition de la fonction nommée "main", 
crée un environnement de variables à partir de [args] 
(normalisées avec la fonction ci-dessus) et de ses paramètres et 
enfin appelle le corps de main sur ces arguments 
(comme un appel de fonction, sauf qu’ici les arguments sont 
directement des objets sémantiques et non syntaxique). 
Elle est au fond similaire à un appel de fonction, 
mais un peu plus technique, donc on vous la fourni.*)

let interpret_prg prg args =
    let functions = Util.Environment.new_environment () in
    List.iter (interpret_func_decl functions) prg;
    let environnement = Util.Environment.new_environment () in
    let params, body =
        try Option.get (Util.Environment.get functions "main")
        with _ -> failwith "Function main not defined!"
    in
    let vars = List.map (fun (_, _, v) -> v) params in
    let args = normalize_arg_list args vars in
    List.iter2
        (fun v a ->
            Abstract_machine.parse_complex_argument_and_affect environnement v a)
        vars args;
    try interpret_instruction environnement functions body
    with Return_exp _ -> ()
