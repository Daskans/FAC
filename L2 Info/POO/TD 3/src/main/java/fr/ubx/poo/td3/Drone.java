package fr.ubx.poo.td3;

public class Drone extends Vehicle {

    
    public Drone(String name, Position position, double energy, double cost) {
        super(name, position, energy, cost);
    }


    @Override int distance(Position target) {
        return (int)Math.sqrt(Math.pow(target.getX()-getPosition().getX(), 2) + Math.pow(target.getY()-getPosition().getY(), 2));
    }


    @Override Position[] getPathTo(Position target) {
        Position[] Movement_Array = new Position[1];
        Movement_Array[0] = new Position(target.getX(), target.getY());
        return Movement_Array;
    }
    
}
