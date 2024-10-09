package fr.ubx.poo.td6.model;

import java.util.*;

public class Node<T> {
    private final T data;
    private final List<Node<T>> neighbours;

    public Node(T data) {
        this.data = data;
        this.neighbours = new ArrayList<>();
    }

    public T getData() { return data;}

    public void addEdge(Node to) {
        neighbours.add(to);
    }

    public List<Node<T>> getNeighbours() { return neighbours;}
}


