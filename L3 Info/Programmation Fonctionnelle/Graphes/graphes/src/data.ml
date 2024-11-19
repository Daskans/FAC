(*** Examples of graphs created from external format *)
open Graph_input

let s5 = graph_from_earcs ~name:"s5" ~enodes:[1; 2; 3] []
let g1 = graph_from_earcs ~name:"g1" ~enodes:[3] [(1,2)]
let g2 = graph_from_earcs ~name:"g2" [(2, 1); (3, 2); (4, 2); (4, 1); (1, 3)]
let g3 = graph_from_earcs ~name:"g3" [(1,2); (2,3); (3,4); (5,6)]
let g4 = graph_from_earcs ~name:"g4" [(1,2); (2,3); (3,4); (4,1)]
let g_complete =
  graph_from_earcs ~name:"g_complete"
    [(1,2); (1,3); (1,4); (1,5); (2,3); (2,4); (2,5); (3,4); (3,5); (4,5)]

let g_eulerian1 =
  graph_from_earcs ~name:"g_eulerian" [(1,2); (2,3); (3,4); (4,1)]
let g_eulerian2 = graph_from_earcs ~name:"g_eulerian"
                   [(1,2); (1,3); (2,3); (3,4); (3,5); (4,5)]
let go1 = graph_from_earcs ~name:"go1" ~oriented:true [(1,2)]
let go2 = graph_from_earcs ~name:"go2" ~oriented:true [(1,2); (2,3)]
let go3 = graph_from_earcs ~name:"go3" ~oriented:true [(1,2); (2,3); (3, 1)]
let go4 = graph_from_earcs ~name:"go4" ~oriented:true [(1,2); (2,3); (1, 3)]
let go5 = graph_from_earcs ~name:"go5" ~oriented:true [(1,2); (2,3); (3, 1); (4, 2)]
let go6 = graph_from_earcs ~name:"go6" ~oriented:true [(1,2); (2,3); (3,4); (4,1)]
let go7 = graph_from_earcs ~name:"go7" ~oriented:true [(1,2); (1,3); (3,4); (4,1)]
let gep = graph_from_epaths ~name:"gep" ~oriented:true [[1;2;3;5;6]; [1;5;4]]
let g8 = oriented_to_non_oriented ~name:"g8" gep

let go_complete = graph_from_earcs ~name:"go_complete" ~oriented:true [(1,2); (1,3); (2,1); (2,3); (3,1); (3,2)]

let g_petersen = graph_from_earcs ~name:"g_petersen"
                   [(1,2); (1,5); (1,9); (2,3); (2,7); (3,4); (3,10); (4,5);
 (4,8); (5,6); (6,7); (6,10); (7,8); (8,9); (9,10)]

let g_stable = graph_from_earcs ~name:"g_stable" ~enodes:[1; 2; 3] []
