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

    public boolean isConnected() {
        Hashtable<T, Boolean> visited = new Hashtable<>();
        nodes.forEach(node -> visited.put(node.getData(), false));
        if (nodes.stream().findFirst().isPresent()) {
            Node<T> source = nodes.stream().findFirst().get();
            dfs(source, visited);
        }
        return ! visited.containsValue(false);
    }

}
