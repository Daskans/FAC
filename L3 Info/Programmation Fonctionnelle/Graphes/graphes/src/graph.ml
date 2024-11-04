open Dict
(*** Implémentation of a graph library vertex-oriented *)

(** node and arc *)

(** a node contains a dictionary containing its output arcs *)
(** an arc is represented by its origin node et extremity node. *)
(** a set of nodes is represented with a dictionary.
    The key is the num of the node *)
(** a set of arcs is represented with a dictionary.
    The key is the pair of the num of its nodes (origin, extremity) *)

(** a node in a graph is a unique object. Nodes can be compared with == *)
type node = { mutable num : int; out_arcs : arcs; mutable mark : bool }
and arc = { origin : node; extremity : node }
and arcs = (int * int, arc) dict
and nodes = (int, node) dict

(** key of node *)
let node_key node = node.num

(** create an arc from its origin and extremity nodes *)
let make_arc origin extremity = { origin = origin; extremity = extremity }

(** origin node of an arc *)
let arc_origin arc = arc.origin

(** extremity node of an arc *)
let arc_extremity arc = arc.extremity

(** create an inverse arc *)
let inverse_arc arc = make_arc (arc_extremity arc) (arc_origin arc)

(** key of an arc (to find an arc in an arc dictionary *)
let arc_key arc = node_key (arc_origin arc), node_key (arc_extremity arc)

(** size of a dictionary of nodes *)
let nodes_size (nodes : nodes) = dict_size nodes

(** size of a dictionary of arcs *)
let arcs_size (arcs : arcs) = dict_size arcs

(** a node from a node dictionary *)
let nodes_first (nodes : nodes) = dict_first nodes

(** an arc from an arc dictionary *)
let arcs_first (arcs : arcs) = dict_first arcs

(** dict of the outarcs of a node *)
let node_out_arcs node = node.out_arcs

(** mark of node *)
let node_mark node = node.mark

(** is node marked *)
let node_marked_p node = node_mark node

(** is node unmarked *)
let node_unmarked_p node = not (node_mark node)

(** set the mark of node *)
let mark_node node = node.mark <- true

(** unset the mark of node *)
let unmark_node node = node.mark <- false

(** number of out_arcs of nodes *)
let node_out_degree node = dict_size (node_out_arcs node)

(** create an empty dictionary of nodes *)
let make_empty_nodes () : nodes = make_dict ()

(** create an empty dictionary of arcs *)
let make_empty_arcs () : arcs = make_dict ()

(** is the set of nodes empty? *)
let nodes_empty_p nodes = nodes_size nodes = 0

(** is the set of arcs empty? *)
let arcs_empty_p arcs = arcs_size arcs = 0

(** destructively remove arcs satisfying arc_fun *)
let arcs_delete_if arc_fun arcs = dict_delete_if arc_fun arcs

(** destructively remove arcs not satisfying arc_fun *)
let arcs_delete_if_not arc_fun arcs = dict_delete_if_not arc_fun arcs

let arcs_remove_if arc_fun arcs = dict_remove_if arc_fun arcs
let arcs_remove_if_not arc_fun arcs = dict_remove_if_not arc_fun arcs

(** destructively remove nodes satisfying node_fun *)
let nodes_delete_if node_fun nodes = dict_delete_if node_fun nodes

(** destructively remove nodes not satisfying node_fun *)
let nodes_delete_if_not node_fun nodes = dict_delete_if_not node_fun nodes

let nodes_remove_if node_fun nodes = dict_remove_if node_fun nodes
let nodes_remove_if_not node_fun nodes = dict_remove_if_not node_fun nodes

(** find a potential node from its key in the set of nodes (option) *)
let nodes_find_opt num (nodes : nodes) = dict_find_opt num nodes

(** membership of node from its key in the set of nodes *)
let nodes_member node nodes = dict_member (node_key node) nodes

(** membership of arc from its key in the set of arcs *)
let arcs_member arc arcs = dict_member arc arcs

(** destructively add a node to a set of nodes *)
let nodes_insert node nodes = dict_insert (node_key node) node nodes

(** destructively add an arc to a set of arcs *)
let arcs_insert arc arcs = dict_insert (arc_key arc) arc arcs

(** true if every node in nodes satisfies the predicate pred *)
let nodes_every node_pred nodes = dict_every node_pred nodes

(** true if some node in nodes satisfies the predicate pred *)
let nodes_some node_pred nodes = dict_some node_pred nodes

(** true if every arc in arcs satisfies the predicate pred *)
let arcs_every arc_pred arcs = dict_every arc_pred arcs

(** true if some arc in arcs satisfies the predicate pred *)
let arcs_some arc_pred arcs = dict_some arc_pred arcs

(** create a node from its key number *)
let make_node num = { num = num; out_arcs = make_empty_arcs (); mark = false }

(** create a set of arcs from a list of arcs *)
let make_arcs (larcs : arc list) : arcs =
  let arcs = make_empty_arcs () in
  begin
    List.iter (fun arc -> arcs_insert arc arcs) larcs;
    arcs;
  end

(** create a set of nodes from a list of nodes *)
let make_nodes (lnodes : node list) : nodes =
  let nodes = make_empty_nodes () in
  begin
    List.iter (fun node -> nodes_insert node nodes) lnodes;
    nodes;
  end

(** iterate a function on the nodes of the set of nodes *)
let nodes_iter node_fun nodes = dict_iter node_fun nodes

(** iterate a function on the arcs of the set of arcs *)
let arcs_iter arc_fun arcs = dict_iter arc_fun arcs

(** list of the nodes of a set of nodes *)
let nodes_contents nodes = dict_contents nodes

(** copy containing the same nodes *)
let nodes_copy nodes = dict_copy nodes

(** list of the arcs of a set of arcs *)
let arcs_contents arcs = dict_contents arcs

(** A graph has a name, is oriented or not and contains a set of nodes *)
type graph = { name : string; nodes : nodes; mutable oriented : bool }

(** set of nodes of a graph *)
let graph_nodes graph = graph.nodes

(** name of a graph *)
let graph_name graph = graph.name

(** is the graph oriented *)
let graph_oriented_p graph = graph.oriented

(** is the graph unoriented *)
let graph_unoriented_p graph = not graph.oriented

(** create an empty graph with a name and whether it is oriented *)
let make_graph name oriented =
  { name = name; nodes = make_empty_nodes (); oriented = oriented }

(** create and add arc (origin, extremity) to out_arcs of origin node *)
let node_insert_outarc origin extremity =
  arcs_insert (make_arc origin extremity) (node_out_arcs origin)

(** create and add arc (origin, extremity) to out_arcs of origin node
    if graph is unoriented inverse arc is also added *)
let graph_create_arc g origin extremity =
  begin
    assert (nodes_member origin (graph_nodes g));
    assert (nodes_member extremity (graph_nodes g));
    node_insert_outarc origin extremity;
    if not (graph_oriented_p g) then
      node_insert_outarc extremity origin;
    end

(** create and add node num to graph *)
let graph_create_node num graph =
  let node = make_node num in
  begin
    nodes_insert node (graph_nodes graph);
    node;
  end

(** create and add node num to graph if not already there *)
let find_insert_node num graph =
  let r = nodes_find_opt num (graph_nodes graph) in
  match r with
    None -> graph_create_node num graph
  | Some node -> node

(** create the set of arcs of graph from its nodes *)
let graph_arcs graph =
  let arcs = make_empty_arcs ()  in
  begin
  nodes_iter
    (fun node -> (arcs_iter
                    (fun arc -> arcs_insert arc arcs)
                    (node_out_arcs node)))
    (graph_nodes graph);
  arcs;
  end

(** in an unoriented graph an edge is such that the num of origin is less than the num of the extremity *)
let edge_from_arc arc =
  let origin = arc_origin arc and extremity = arc_extremity arc in
  if node_key origin < node_key extremity then
    make_arc origin extremity
  else
    make_arc extremity origin

(** create a set of edges from a set of arcs *)
let edges_from_arcs arcs =
  let edges = make_empty_arcs () in
  begin
    arcs_iter (fun arc -> arcs_insert (edge_from_arc arc) edges) arcs;
    edges
  end

(** create a set of edges from a graph *)
let graph_edges graph = edges_from_arcs (graph_arcs graph)

(** create a set of nodes present in a set of arcs *)
let node_in_arcs node graph =
  let arcs = make_empty_arcs () in
  begin
    arcs_iter
      (fun arc ->
        if node == arc_extremity arc then arcs_insert arc arcs)
      (graph_arcs graph);
    arcs;
  end

(** true if all nodes of nodes are marked *)
let all_nodes_marked_p nodes =
  nodes_every node_marked_p nodes

(** true if all nodes of nodes are unmarked *)
let all_nodes_unmarked_p nodes =
  nodes_every node_unmarked_p nodes

(** destructively unmark nodes of nodes *)
let unmark_nodes nodes =
  nodes_iter unmark_node nodes

(** destructively unmark the nodes of graph *)
let graph_unmark_nodes graph =
  unmark_nodes (graph_nodes graph)

(** destructively mark all nodes accessible from node *)
let rec mark_from node graph =
  if not (node_marked_p node) then
    begin
      mark_node node;
      arcs_iter
        (fun arc -> mark_from (arc_extremity arc) graph) (node_out_arcs node);
      if not (graph_oriented_p graph) then
        arcs_iter
          (fun arc -> mark_from (arc_origin arc) graph) (node_in_arcs node graph);
    end

(** renumber the nodes starting from n; destructive *)
let nodes_renumber_d (nodes : nodes) n =
  let n = ref n in
  nodes_iter (fun node -> begin
                  node.num <- !n;
                  n := succ(!n); end) nodes

(** utils to see better the objects *)
(** because we are not always interested in the details of the objects *)
(** because the contents of the dictionaries are not visible directly *)
(** because I don't find the notion of print_function for objects in OCaML
    as there is in Lisp *)

let node_show node = node_key node
let nodes_show nodes = List.map node_show (nodes_contents nodes)
let arc_show arc = node_key (arc_origin arc), node_key (arc_extremity arc)
let arcs_show arcs = List.map arc_show (arcs_contents arcs)
let graph_show graph =
  nodes_show (graph_nodes graph), arcs_show (graph_arcs graph)

(*
   Printer for arcs and graphs
   Can be installed in the REPL with the following instruction :
   #install_printer Graph.graph_format;;
 *)
let graph_out_arcs_format fmt (arcs : arcs) =
  Format.fprintf fmt "{";
  Hashtbl.iter  (fun (u,v) _ ->
      Format.fprintf fmt "(%d,%d);" u v; )
    arcs;
  Format.fprintf fmt "}"

let graph_format fmt (graph : graph) =
  Format.fprintf fmt "{name = \"%s\"; nodes = {" graph.name;
  nodes_iter (fun elt ->
      Format.fprintf fmt "{num = %d, out_arcs = " elt.num;
      graph_out_arcs_format fmt elt.out_arcs;
      Format.fprintf fmt ", mark = %b}; " elt.mark;
    ) graph.nodes ;
  Format.fprintf fmt "}, oriented = %b}" graph.oriented;
