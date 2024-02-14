package fr.ubx.poo.td.model;

import fr.ubx.poo.td.view.*;

public class Drone extends Vehicle {

    
    public Drone(String name, Position position, double energy, double cost) {
        super(name, position, energy, cost);
    }


    public int distance(Position target) {
        return (int)Math.sqrt(Math.pow(target.x()-getPosition().x(), 2) + Math.pow(target.y()-getPosition().y(), 2));
    }


    public Position[] getPathTo(Position target) {
        Position[] Movement_Array = new Position[1];
        Movement_Array[0] = new Position(target.x(), target.y());
        return Movement_Array;
    }
    
}
