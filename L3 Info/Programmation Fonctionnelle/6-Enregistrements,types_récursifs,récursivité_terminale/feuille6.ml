type date = { day : int; month : int; year : int};;

let today = {day = 1; month = 10; year = 2024};;
let not_today = {day = 24; month = 3; year = 2024};;

let date_infeg date1 date2 =
    if date1.year < date2.year then
        true
    else if date1.month < date2.month then
        true
    else if date1.month = date2.month then
        if date1.day < date2.day then
            true
        else false
    else
        false
;;