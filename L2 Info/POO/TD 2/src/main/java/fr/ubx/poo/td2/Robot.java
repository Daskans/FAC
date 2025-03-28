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
        int length;
        if (Math.abs(target.getX()) > Math.abs(target.getY())) {
            length = Math.abs(target.getX() - getPosition().getX())*2 + 1;
        } else {
            length = Math.abs(target.getY() - getPosition().getY())*2 + 1;
        }
        Position[] Movement_Array = new Position[length + 2];
        Movement_Array[0] = new Position(getPosition().getX(), getPosition().getY());
        for (int i = 1; i < length; i += 2) {
            if (Math.abs(target.getX()) > Math.abs(Movement_Array[i-1].getX())) {
                if (target.getX() > getPosition().getX()) {
                    Movement_Array[i] = new Position(Movement_Array[i-1].getX()+1, Movement_Array[i-1].getY());
                } else {
                    Movement_Array[i] = new Position(Movement_Array[i-1].getX()-1, Movement_Array[i-1].getY());
                }
            if (Math.abs(target.getY()) > Math.abs(Movement_Array[i-1].getY())) {
                } if (target.getY() > getPosition().getY()) {
                    Movement_Array[i+1] = new Position(Movement_Array[i].getX(), Movement_Array[i].getY()+1);
                } else {
                    Movement_Array[i+1] = new Position(Movement_Array[i].getX(), Movement_Array[i].getY()-1);
                }
            }
        }
        Movement_Array[length] = new Position(target.getX(), Movement_Array[length-1].getY());
        Movement_Array[length+1] = new Position(Movement_Array[length].getX(), target.getY());
        return Movement_Array;
    }

    Position getPosition() {
        return new Position(position.getX(), position.getY());
    }


}
