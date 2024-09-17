type mycomplex = C of float * float ;;

let make_complex real imaginary =
    C(real,imaginary)
;;

let realpart complex =
    match complex with
    | C(real,_) -> real
;;

let imagpart complex =
    match complex with
    | C(_,imaginary) -> imaginary
;;

let c_origin = make_complex 0. 0. ;;
let c_i = make_complex 0. 1. ;;
let p_12 = make_complex 1. 2. ;;
let c_test = make_complex (-2.5) (-4.5) ;;

let c_abs c =
    sqrt((realpart c *. realpart c) +. (imagpart c *. imagpart c))
;;

let c_sum c1 c2 =
    make_complex (realpart c1 +. realpart c2) (imagpart c1 +. imagpart c2)
;;

let c_dif c1 c2 =
    make_complex (realpart c1 -. realpart c2) (imagpart c1 -. imagpart c2)
;;

let c_opp c =
    make_complex (-. realpart c) (-. imagpart c)
;;

let c_mul c1 c2 =
    make_complex (realpart c1 *. realpart c2 -. imagpart c1 *. imagpart c2)
                (realpart c1 *. imagpart c2 +. imagpart c1 *. realpart c2)
;;

let c_sca lambda c =
    make_complex (realpart c *. lambda) (imagpart c *. lambda)
;;

let c_exp c =
    make_complex ((exp (realpart c)) *. cos(imagpart c)) ((exp (realpart c)) *. sin(imagpart c))
;;

let c_arg c =
    (realpart c) /. (c_abs c)
;;

let translate c vector =
    c_sum c vector
;;

let rotate0 c angle =
    make_complex (realpart c *. angle) (imagpart c *. angle)
;;

let rotate c angle vector =
    