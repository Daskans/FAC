package fr.ubx.poo.td.model;

import fr.ubx.poo.td.World;
import fr.ubx.poo.td.view.*;

abstract public class Vehicle {
    final double cost;
    String name;
    private Position position;
    double energy;
    public boolean isMoving = false;

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
        if (!isMoving) {
            if (canMove(target)) {
                Position lastPos = getPosition();
                Position[] path = getPathTo(target);
                for (int i = 0; i < path.length; i++) {
                    position = path[i];
                    if (World.get(position) == World.DUST) {
                        energy -= cost*0.2;
                    }
                    energy -= distance(lastPos)*cost;
                    System.out.println("Moving : " + getClass().getSimpleName() + " " + name + " : energy=" + energy);
                    lastPos = path[i];
                }
                System.out.println("Move completed : " + getClass().getSimpleName() + " " + name + " : energy=" + energy);
            } else {
                System.err.println("too far");
            }
        }
    }

    abstract public  Position[] getPathTo(Position target);

    public Position getPosition() {
        return new Position(position.x(), position.y());
    }
}
