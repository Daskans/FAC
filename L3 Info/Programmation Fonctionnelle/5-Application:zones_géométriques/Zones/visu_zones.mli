val nb_pixels_per_unit : int
val int_to_nb_pixels : int -> int
val pixel_to_float : int -> float
val pixel_to_point : int -> int -> Mycomplex.mycomplex
val zone_to_pixels :
  (Mycomplex.mycomplex -> bool) -> int -> Graphics.color array array
val pixels_to_png : Graphics.color array array -> string -> unit
val zone_to_png : (Mycomplex.mycomplex -> bool) -> int -> string -> unit
val random_sign : 'a -> float
val random_signed_float : float -> float
val random_point : float -> Mycomplex.mycomplex
val uname : unit -> string
val viewer : string
val view_file : string -> Unix.process_status
val view_zone_size :
  (Mycomplex.mycomplex -> bool) -> int -> Unix.process_status
val view_zone : (Mycomplex.mycomplex -> bool) -> Unix.process_status
