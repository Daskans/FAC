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

        int actualX = getPosition().x();
        int actualY = getPosition().y();
        int distanceT = distance(target);
        int length = distanceT + Math.abs(target.x()-target.y());
        if (length % 2 == 0) {
            length += 1;
        } else {
            length += 2;
        }
        
        boolean stop = false;

        Position[] Movement_Array = new Position[length];
        Movement_Array[0] = new Position(actualX, actualY);
        System.out.println("length: " + length + " distanceT: " + distanceT + " | ick" + Math.abs(target.x()-target.y()));
        System.out.println("actualX: " + actualX + " actualY: " + actualY);
        System.out.println("target position: " + target.x() + " " + target.y());
        int i = 1;
        for (; (actualX != target.x() || actualY != target.y()) && i < length; i+=2) {
            if (target.x() != actualX) {
                if (actualX < target.x()) {
                    actualX++;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualX--;
                        stop = true;
                        break;
                    }
                } else if (actualX > target.x()) {
                    actualX--;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualX++;
                        stop = true;
                        break;
                    }
                }
                Movement_Array[i] = new Position(actualX, actualY);
                System.out.println(" X move -> actualX: " + actualX + " actualY: " + actualY + " | i: " + i);
            } else {
                Movement_Array[i] = new Position(actualX, actualY);
                System.out.println(" X move (N) -> actualX: " + actualX + " actualY: " + actualY + " | i: " + i);
            }

            if (target.y() != actualY) {
                if (actualY < target.y()) {
                    actualY++;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualY--;
                        stop = true;
                        break;
                    }
                } else if (actualY > target.y()) {
                    actualY--;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualY++;
                        stop = true;
                        break;
                    }
                }
                Movement_Array[i+1] = new Position(actualX, actualY);
                System.out.println(" Y move -> actualX: " + actualX + " actualY: " + actualY + " | i: " + (i+1));
            } else {
                Movement_Array[i+1] = new Position(actualX, actualY);
                System.out.println(" Y move (N) -> actualX: " + actualX + " actualY: " + actualY + " | i: " + (i+1));
            }
        }
        for (; i < length; i++) {
            Movement_Array[i] = new Position(actualX, actualY);
        }
        return Movement_Array;
    }
}
