package fr.ubx.poo.td3;

public class Robot extends Vehicle {


    public Robot(String name, Position position, double energy, double cost) {
        super(name, position, energy, cost);
    }


    @Override int distance(Position target) {
        return Math.abs(target.getX()-getPosition().getX()) + Math.abs(target.getY()-getPosition().getY());
    }


    @Override Position[] getPathTo(Position target) {
        Position[] Movement_Array = new Position[2];
        Movement_Array[0] = new Position(target.getX(), getPosition().getY());
        Movement_Array[1] = new Position(target.getX(), target.getY());
        return Movement_Array;
    }
    /*
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
    }*/
}
