open Graph

(** print NODE to STREAM in Dot format *)
let print_node node stream =
  begin
    Printf.fprintf stream "n%d " (node_key node);
    Printf.fprintf stream "[color=";
    if node_marked_p node then
      Printf.fprintf stream "red"
    else
      Printf.fprintf stream "black";
    (*    Printf.fprintf stream "%c" '\"'; *)
    Printf.fprintf stream "]";
  end

(** print ARC to STREAM in Dot format *)
let print_arc arc oriented stream =
  let o, e = arc_origin arc, arc_extremity arc in
  begin
    if oriented then
      Printf.fprintf stream "n%d -> n%d" (node_key o) (node_key e)
    else
      Printf.fprintf stream "n%d -- n%d" (node_key o) (node_key e);
    Printf.fprintf stream ";\n";
  end

(** print a set of arcs ARCS to STREAM in Dot format *)
let print_arcs arcs oriented stream =
  arcs_iter (fun arc -> print_arc arc oriented stream) arcs

(** print a set of nodes NODES to STREAM in Dot format *)
let print_nodes nodes stream =
  nodes_iter (fun node -> begin
                  print_node node stream;
                  Printf.fprintf stream ";\n" ;
                end)
    nodes

let out_name name = "g_" ^ name
let dot_name name = out_name name ^ ".dot"
let pdf_name name = out_name name ^ ".pdf"

(** print GRAPH to STREAM in Dot format *)
let graph_to_dot graph stream =
  let oriented = graph_oriented_p graph in
  begin
    if oriented then
      Printf.fprintf stream "digraph %s {\n" (graph_name graph)
    else Printf.fprintf stream "graph %s {\n" (graph_name graph);
    print_nodes (graph_nodes graph) stream;
    print_arcs
      (if oriented then graph_arcs graph else graph_edges graph)
      (graph_oriented_p graph) stream;
    Printf.fprintf stream "}\n";
  end

(** save GRAPH to file with name depending on the name of the graph *)
let graph_to_dot_file graph =
  let stream = open_out (dot_name (graph_name graph)) in
  begin
    graph_to_dot graph stream;
    close_out stream;
  end

(** convert a Dot file to pdf format for future viewing *)
let dot_to_pdf name =
  ignore (Sys.command ("dot -Tpdf " ^ dot_name name ^ " -o " ^ pdf_name name))

(** visualize GRAPH *)
let graph_view graph =
  let name = graph_name graph in
  begin
    graph_to_dot_file graph;
    dot_to_pdf name;
    ignore (Sys.command ("evince " ^ pdf_name name));
  end
