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



    
let earcs_from_epaths epaths =
    let rec see_path epath result =
        match epath with
        | [] -> result
        | path::rest ->
            let rec make_couple path_ result_ =
                match path_ with
                | [] -> result_
                | s::[] -> result_
                | s::tail -> make_couple tail ((s, List.hd tail)::result_)
            in (make_couple path result) @ (see_path rest result)
    in see_path epaths []
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


let oriented_to_non_oriented ?(name="g") graph =
    let g = make_graph name (not (graph_oriented_p graph)) in
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