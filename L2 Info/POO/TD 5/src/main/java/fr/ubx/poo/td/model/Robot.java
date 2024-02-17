package fr.ubx.poo.td.model;

import fr.ubx.poo.td.view.*;

public class Robot extends Vehicle {


    public Robot(String name, Position position, double energy, double cost) {
        super(name, position, energy, cost);
    }


    public int distance(Position target) {
        return Math.abs(target.x()-getPosition().x()) + Math.abs(target.y()-getPosition().y());
    }


    public Position[] getPathTo(Position target) {
        Position[] Movement_Array = new Position[2];
        Movement_Array[0] = new Position(target.x(), getPosition().y());
        Movement_Array[1] = new Position(target.x(), target.y());
        return Movement_Array;
    }
    /*
    Position[] getPathTo(Position target) {
        int length;
        if (Math.abs(target.x()) > Math.abs(target.y())) {
            length = Math.abs(target.x() - getPosition().x())*2 + 1;
        } else {
            length = Math.abs(target.y() - getPosition().y())*2 + 1;
        }
        Position[] Movement_Array = new Position[length + 2];
        Movement_Array[0] = new Position(getPosition().x(), getPosition().y());
        for (int i = 1; i < length; i += 2) {
            if (Math.abs(target.x()) > Math.abs(Movement_Array[i-1].x())) {
                if (target.x() > getPosition().x()) {
                    Movement_Array[i] = new Position(Movement_Array[i-1].x()+1, Movement_Array[i-1].y());
                } else {
                    Movement_Array[i] = new Position(Movement_Array[i-1].x()-1, Movement_Array[i-1].y());
                }
            if (Math.abs(target.y()) > Math.abs(Movement_Array[i-1].y())) {
                } if (target.y() > getPosition().y()) {
                    Movement_Array[i+1] = new Position(Movement_Array[i].x(), Movement_Array[i].y()+1);
                } else {
                    Movement_Array[i+1] = new Position(Movement_Array[i].x(), Movement_Array[i].y()-1);
                }
            }
        }
        Movement_Array[length] = new Position(target.x(), Movement_Array[length-1].y());
        Movement_Array[length+1] = new Position(Movement_Array[length].x(), target.y());
        return Movement_Array;
    }*/
}
