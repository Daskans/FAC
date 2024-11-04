(*** mutable dictionaries *)
open Utils

(** dictionaries implemented with hashtables *)
let ht_init_size = 10
type ('k, 'v) dict = ('k, 'v) Hashtbl.t

(** creates an empty dictionary *)
let make_dict () = Hashtbl.create ht_init_size

(** search obj in dictionary dict with key *)
let dict_find_opt key dict = Hashtbl.find_opt dict key

(** membership in dictionary dict with key *)
let dict_member key dict = dict_find_opt key dict <> None

(** number of bindings key-obj in dictionary dict *)
let dict_size dict = Hashtbl.length dict

(** emptiness of dictionary dict *)
let dict_empty_p dict = dict_size dict = 0

(** iterate a function obj_fun on every obj of dictionary dict *)
let dict_iter obj_fun dict = Hashtbl.iter (fun _ obj -> obj_fun obj) dict

(** destructively add key-obj to the dictionary dict *)
let dict_insert key obj dict = Hashtbl.replace dict key obj (* destructive *)

(** destructively remove key-obj from the dictionary dict *)
let dict_delete key dict = Hashtbl.remove dict key (* destructive *)

(** New dictionary containing the SAME objects dictionary dict *)
let dict_copy dict = Hashtbl.copy dict

(** destructively deletes objects satisfying pred from the dictionary dict *)
let dict_delete_if obj_pred dict =
  Hashtbl.iter (fun k obj -> if obj_pred obj then Hashtbl.remove dict k) dict
 
(** copy of dict without objects satisfying obj_pred *)
let dict_remove_if obj_pred dict =
  let d = dict_copy dict in
  begin
    dict_delete_if obj_pred d;
    d;
  end

(** destructively deletes objects not satisfying pred from the dictionary dict *)
let dict_delete_if_not obj_pred dict =
  dict_delete_if (fun obj -> not (obj_pred obj)) dict

(** copy of dict with objects satisfying obj_pred *)
let dict_remove_if_not obj_pred dict =
  dict_remove_if (fun obj -> not (obj_pred obj)) (dict_copy dict)

(** list of objs containent in the dicitonary dict *)
let dict_contents dict =
  let objs = ref [] in
  begin
    dict_iter (fun obj -> objs := obj :: !objs) dict;
    !objs
  end

(** returns an element of a non empty dictionary *)
let dict_first dict = List.nth (dict_contents dict) 0

(** returns true if all objects the dictionary satisfy the predicate pred *)
let dict_every pred dict = every pred (dict_contents dict)

(** returns true if some object in the dictionary satisfy the predicate pred *)
let dict_some pred dict = some pred (dict_contents dict)

(** returns no object in the dictionary satisfy the predicate pred *)
let dict_none pred dict = none pred (dict_contents dict)
