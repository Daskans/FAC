package fr.ubx.poo.td.model;

import fr.ubx.poo.td.view.*;

abstract public class Vehicle {
    final double cost;
    String name;
    private Position position;
    double energy;

    public Vehicle(String name, Position position, double energy, double cost) {
        this.name = name;
        this.position = new Position(position.x(), position.y());
        this.energy = energy;
        this.cost = cost;
    }

    public int range() {
        return (int) Math.round(energy/cost);
    }

    abstract public int distance(Position target);

    public boolean canMove(Position target) {
        return distance(target) <= range();   
    }

    public void move(Position target) {
        if (canMove(target)) {
            energy -= distance(target) * cost;
            position = position.translate(target.x()-getPosition().x(), target.y()-getPosition().y());
        } else {
            System.err.println("too far");
        }
        System.out.println("Move completed : " + getClass().getSimpleName() + " " + name + " : energy=" + energy);
    }

    abstract public  Position[] getPathTo(Position target);

    public Position getPosition() {
        return new Position(position.x(), position.y());
    }
}
