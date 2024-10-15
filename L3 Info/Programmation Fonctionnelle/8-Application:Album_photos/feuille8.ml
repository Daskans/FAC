(* EXERCICE 1 *)

type subject= Selfie | Monument | Mirror_of_Water | Fashion | People| My_plate_at_the_restaurant
type photo = Photo of int * (subject list)
type album = photo list

let test_photo = Photo(2016, [Selfie; Mirror_of_Water])

let my_album =
    [Photo(2016, [Selfie; Mirror_of_Water]);
    Photo(2014, [Selfie; People]);
    Photo(2014, [Selfie; Monument; Fashion]);
    Photo(2012, [My_plate_at_the_restaurant; People])]


let photo_year photo =
    match photo with
    | Photo(year,_) -> year


let photo_subjects photo =
    match photo with
    | Photo(_,subjects) -> subjects


let rec has_subject subject photo =
    match photo_subjects photo with
    | [] -> false
    | head::tail ->
        if head = subject then
            true
        else
            has_subject subject (Photo(0,tail))


let rec select_by_subject subject album =
    match album with
    | [] -> []
    | (photo::tail) ->
        if has_subject subject photo then
            photo::(select_by_subject subject tail)
        else
            (select_by_subject subject tail)


let rec select_by_year is_year album =
    match album with
    | [] -> []
    | (photo::tail) ->
        if is_year (photo_year photo) then
            photo::(select_by_year is_year tail)
        else
            (select_by_year is_year tail)


let test =
    begin
        assert(photo_year test_photo = 2016);
        assert(photo_subjects test_photo = [Selfie; Mirror_of_Water]);
        assert(has_subject Selfie test_photo = true);
        assert(has_subject People test_photo = false);
        assert(select_by_subject Selfie my_album = [Photo(2016, [Selfie; Mirror_of_Water]);
                                                    Photo(2014, [Selfie; People]);
                                                    Photo(2014, [Selfie; Monument; Fashion])]);
        assert(select_by_year (fun x -> x <= 2014) my_album = [Photo (2014, [Selfie; People]);
                                                            Photo (2014, [Selfie; Monument; Fashion]);
                                                            Photo(2012, [My_plate_at_the_restaurant; People])]);                                           
    end
;;

(* EXERCICE 2 *)

type criteria =
    Subject of subject
    | Date of (int -> bool)
    | Or of criteria * criteria
    | And of criteria * criteria
    | Not of criteria

let my_criteria = And(And(Subject(Selfie),Not(Subject(People))),Date(fun x -> x >= 2014))

let rec satisfies criteria photo =
    match criteria with
    | Subject(subject) -> has_subject subject photo
    | And(a, b) -> (satisfies a photo) && (satisfies b photo)
    | Or(a, b) -> (satisfies a photo) || (satisfies b photo)
    | Date(is_year) -> is_year (photo_year photo)
    | Not(a) -> not(satisfies a photo)


let rec select criteria album =
    match album with
    | [] -> []
    | photo::tail ->
        if satisfies criteria photo then
            photo::(select criteria tail)
        else
            select criteria tail


let test =
    begin
        assert(select my_criteria my_album = [Photo (2016, [Selfie; Mirror_of_Water]);
                                            Photo (2014, [Selfie; Monument; Fashion])]);
    end
;;