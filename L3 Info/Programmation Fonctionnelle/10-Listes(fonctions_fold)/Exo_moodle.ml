let seq_max_len l e =
    let rec aux l e result max_result=
        match l with
        | [] -> max_result
        | head::tail ->
            if head = e then
                if result = max_result then
                    aux tail e (result + 1) (max_result + 1)
                else
                    aux tail e (result + 1) (max_result)
            else
                aux tail e 0 max_result
    ; in aux l e 0 0
;;