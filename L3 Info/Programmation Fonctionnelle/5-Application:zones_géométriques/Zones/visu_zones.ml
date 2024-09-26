(* visualisation *)

(* for repl *)
(*
 #require "graphics"
  #load "images.cmo"
 #load "zones.cmo"
*)
(* *)
(*
#use "mycomplex.ml"
#use "zones.ml"
#load "images.cmo"
*)
(* for compilation *)

open Mycomplex
open Zones
open Images
open Graphics

let nb_pixels_per_unit = 5

let int_to_nb_pixels n = nb_pixels_per_unit * n

let pixel_to_float x = (float_of_int x) /. (float_of_int nb_pixels_per_unit)

let pixel_to_point px py =
  make_point (pixel_to_float px) (pixel_to_float py)

let zone_to_pixels zone n =
  let nb_pixels = int_to_nb_pixels n in
  let pixels = Array.make_matrix nb_pixels nb_pixels black in
  for l = 0 to nb_pixels - 1 do
    for c = 0 to nb_pixels - 1 do
      pixels.(l).(c) <-
        if l = nb_pixels / 2 || c = nb_pixels  / 2 then Graphics.green
        else if point_in_zone_p (pixel_to_point c (nb_pixels - l)) zone then Graphics.red
             else Graphics.white
    done
  done;
  pixels

let pixels_to_png pixels filename = sauver_image pixels filename
						 
let zone_to_png zone n filename = pixels_to_png (zone_to_pixels zone n) filename

let random_sign _ = let i = Random.int 2 in let sign = if i = 0 then 1 else (-1) in
   float_of_int sign

let random_signed_float z = random_sign () *. Random.float z

let random_point z = make_point (random_signed_float z) (random_signed_float z)

(*
let gruyere n =
  let radius = 40. in
  let zone = ref (make_disk0 radius)
  and disk = make_disk0 (radius /. 20.) in
  for i = 0 to n do
    zone := zone_difference !zone (translate_zone disk (random_point radius))
  done;
  !zone
*)

let uname () =
  let (inchannel, outchannel) = Unix.open_process "uname" in
  let name = input_line inchannel in
  close_in inchannel;
  close_out outchannel;
  name

let viewer = 
  let uname = uname() in
  if uname = "Linux" then "eog " (* open marche aussi maintenant sur ubuntu 20.4 *)
  else if uname = "Darwin" then "open "
  else failwith "Viewer not set under windows"

(* zone_to_png (gruyere 5) 50 "monimage.png" *)

let view_file file =
  Unix.system (viewer ^ file ^ "&")
	      

let view_zone_size zone pixel_size =
  begin
    let filename = "monimage.png" and size = float_of_int pixel_size /. 2. in
    (*let zone = zone in*)
    let zone = translate_zone zone (make_complex size size) in
    zone_to_png zone pixel_size filename;
    view_file filename;
  end
    
let view_zone zone = view_zone_size zone 100

(* Try
   let z1 = zone_difference 
               (make_disk0 20.) 
               (translate_zone (make_rectangle 10. 15.) (make_point 3. 3.))
   let z2 = translate_zone (make_disk 15. (make_point 10. 15.) (make_point 10. 5.)
   let _ = view_zone (zone_union z1 z2)
 *)
