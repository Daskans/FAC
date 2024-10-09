package fr.ubx.poo.td6.model;

import java.util.*;

public class Graph<T> {
    private final Set<Node<T>> nodes;

    public Graph() {  this.nodes = new HashSet<>();}

    public void addNode(T data) {
        Node<T> node = new Node<>(data);
        nodes.add(node);
    }

    public Node<T> getNode(T data) {
        for (Node<T> node : nodes) {
            if (node.getData().equals(data)) {
                return node;
            }
        }
        return null;
    }

    public Set<Node<T>> getNodes() { return nodes;}

    double HeuristicValue(Node<Position> start, Node<Position> end) {
        return Math.sqrt(Math.pow(start.getData().x() - end.getData().x(), 2) + Math.pow(start.getData().y() - end.getData().y(), 2));
    }

    public List<Node<Position>>reconstruct_path(Node<Position> cameFrom[], Node<Position> current) {
        List<Node<Position>> total_path = new ArrayList<>();
        for (int i = cameFrom.length - 1; i >= 0; i--) {
            total_path.add(cameFrom[i]);
        }
        total_path.add(current);
        return total_path;
    }

    public List<Node<Position>> AStar(Node<Position> start, Node<Position> end) {
        // The set of discovered nodes that may need to be (re-)expanded.
        // Initially, only the start node is known.
        // This is usually implemented as a min-heap or priority queue rather than a hash-set.
        Queue<Node<Position>> openSet = new PriorityQueue<>();
        openSet.add(start);

        // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from the start
        // to n currently known.
        Map<Node<Position>, Node<Position>> cameFrom = new HashMap<>();

        // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
        Map<Node<Position>, Double> gScore = new HashMap<>();
        
        
        return null;
    }

}
