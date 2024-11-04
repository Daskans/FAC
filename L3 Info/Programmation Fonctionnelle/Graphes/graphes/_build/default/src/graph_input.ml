open Graph

(** to enter graphs from an external format *)

(** create an arc in GRAPH from the pair EARC which contains the numbers of the origin node and extremity node of the created arc *)

let graph_create_arc_from_earc graph earc =
    let origin, extremity = fst earc, snd earc in
    graph_create_arc
        graph
        (find_insert_node origin graph)
        (find_insert_node extremity graph)

(** add external arcs to GRAPH *)
let fill_graph_from_earcs graph earcs =
    List.iter
        (fun earc -> let _ = graph_create_arc_from_earc graph earc in ())
        earcs


(** insert additional nodes to GRAPH *)
let add_enodes_to_graph enodes graph =
    List.iter (fun enode ->
         let _ = find_insert_node enode graph in ()) enodes

(** create a graph from a list of external arcs and possibly a list of external nodes *)
let graph_from_earcs ?(oriented=false) ?(name="g") ?(enodes=[]) earcs =
    let graph = make_graph name oriented in
    begin
        fill_graph_from_earcs graph earcs;
        add_enodes_to_graph enodes graph;
        graph;
    end

let rec earcs_from_epaths epaths =
    [(1,2)]
    (*match epaths with
    | [] -> []
    | head::tail ->
        let rec aux result =
            match head with
            | head2::tail2 ->
                if tail2 = [] then
                    result
                else
                    aux ((head2, List.hd tail2)::result)
            | _ -> failwith "nique ta mère"
        in (aux []) @ earcs_from_epaths tail*)
;;


(** create a graph from a list of external path*)
let graph_from_epaths ?(oriented=false) ?(name="g") epaths =
    graph_from_earcs ~name:name ~oriented:oriented (earcs_from_epaths epaths)
;;



(** deep copy of a graph. 
    The created graph has no node in common with the original graph *)
let graph_copy graph =
    let g = make_graph (graph_name graph ^ "_copy") (graph_oriented_p graph) in
    begin
        nodes_iter
            (fun node -> let _ = graph_create_node (node_key node) g in ())
            (graph_nodes graph);
        arcs_iter
            (fun arc ->
                graph_create_arc_from_earc g (node_key (arc_origin arc), node_key (arc_extremity arc)))
            (graph_arcs graph);
            g;
        end
