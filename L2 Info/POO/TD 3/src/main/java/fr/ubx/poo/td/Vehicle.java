package fr.ubx.poo.td;

public abstract class Vehicle {
    final double cost;
    String name;
    Position position;
    double energy;

    public Vehicle(String name, Position position, double energy, double cost) {
        this.name = name;
        this.position = new Position(position.getX(), position.getY());
        this.energy = energy;
        this.cost = cost;
    }

    int range() {
        return (int) Math.round(energy/cost);
    }

    abstract int distance(Position target);

    boolean canMove(Position target) { 
        return distance(target) <= range();   
    }

    void move(Position target) {
        if (canMove(target)) {
            energy -= distance(target) * cost;
            position.translate(target.getX()-getPosition().getX(), target.getY()-getPosition().getY());
        } else {
            System.err.println("too far");
        }
        System.out.println("Move completed : " + getClass().getSimpleName() + " " + name + " : energy=" + energy);
    }

    abstract Position[] getPathTo(Position target);

    public Position getPosition() {
        return new Position(position.getX(), position.getY());
    }
}
