let test_mycomplex () =
  begin
(* realpart *)
  assert (let c = make_complex 3. 4. in realpart c = 3.0);

(* imagpart *)
  assert (let c = make_complex 3. 4. in imagpart c = 4.0);

(* c_abs *)
assert (let i = make_complex 0. 1. in c_abs i = 1.);

    assert (let c = make_complex 3. 4. in c_abs c = 5.);
(* c_sum *)
assert (let o = make_complex 0. 0. and i = make_complex 0. 1. in c_sum o i = i);
(* c_sca *)
assert (let c = make_complex 3. 4. in c_sum c c = c_sca 2. c);
assert (let c = make_complex 3. 4. in c_sca 2. c = C(6., 8.));
(* c_dif *)
assert (let c = make_complex 3. 4. and o = make_complex 0. 0. in c_dif c c = o);

(* c_mul *)
assert (let c = make_complex 3. 4. in c_mul c c = C(-7., 24.));
(* c_opp *)
assert (let c = make_complex 3. 4. in c_opp c = C(-3., -4.));

(* c_exp *)
assert (let c = make_complex 3. 4. in c_exp c = C(-13.1287830814621582, -15.2007844630679543));

(* translate *)
assert (let c = make_complex 3. 4. and v = make_complex 2. 3. in translate c v = C(5., 7.));

(* rotate0 *)
assert (let c = make_complex 3. 4. and angle = 3.14159265358979312 /. 4. in rotate0 c angle =  C (-0.707106781186547, 4.94974746830583268));

(* rotate *)
assert (let c = C(3., 4.) and angle = 3.14159265358979312 /. 4. and center = C(1.,2.) in rotate c angle center =  C (1.00000000000000022, 4.82842712474619));
end

(* pour tester vos fonctions *)
(* let _ = test_mycomplex () *)
