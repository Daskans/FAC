package fr.ubx.poo.td2;

public class Robot {
    final double cost;
    String name;
    Position position;
    double energy;


    public Robot(String name, Position position, double energy, double cost) {
        this.name = name;
        this.position = new Position(position.getX(), position.getY());
        this.energy = energy;
        this.cost = cost;
    }

    // TODO
    // Robot's range of action
    int range() {
        return (int) Math.round(energy/cost);
    }

    // TODO
    // Manhattan distance between the robot and the target
    int distance(Position target) {
        return Math.abs(target.getX()-getPosition().getX()) + Math.abs(target.getY()-getPosition().getY());
    }

    // TODO
    // Can the robot move to the target position?
    boolean canMove(Position target) { 
        return distance(target) <= range();   
    }

    // TODO
    // Actions to perform when the robot moves to the target: update the robot's coordinates, remaining energy, etc.
    void move(Position target) {
        if (canMove(target)) {
            energy -= distance(target) * cost;
            position.translate(target.getX()-getPosition().getX(), target.getY()-getPosition().getY());
        } else {
            System.err.println("too far");
        }
        System.out.println("-----------\nrange : "+range()+"\ndistance : "+distance(target)+"\nenergy : "+energy+"\n("+getPosition().getX()+", "+getPosition().getY()+")");
    }

    // TODO
    // Calculate the path between the robot and the target to be reached
    Position[] getPathTo(Position target) {
        Position[] Movement_Array = new Position[distance(target)];
        Movement_Array[0] = new Position(target.getX(), getPosition.getY());
        if (target.getX() > target.getY()) {
            for (int i = 1; i < target.getY(); i++) {
                
            }
        }
            
        return Movement_Array;
    }

    Position getPosition() {
        return new Position(position.getX(), position.getY());
    }


}
