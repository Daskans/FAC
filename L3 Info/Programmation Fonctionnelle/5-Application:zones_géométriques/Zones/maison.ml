
let maison =
  let r = make_rectangle 26. 26.
  and porte = translate_zone (make_rectangle 8. 12.) (make_point 9. 0.)
  and toit = translate_zone (rotate_zone0 (make_rectangle 18.385 18.385) (Float.pi /. 4.)) (make_point 0. 26.) in
  let corps = zone_difference (zone_union toit r) porte
  and fenetre = make_disk0 3. in
      zone_difference
      (zone_difference corps
		     (translate_zone fenetre (make_point 6.5 20.)))
      (translate_zone fenetre (make_point 19.5 20.))
