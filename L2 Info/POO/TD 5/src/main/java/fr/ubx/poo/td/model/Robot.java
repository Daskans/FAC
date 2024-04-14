package fr.ubx.poo.td.model;

import fr.ubx.poo.td.*;
import fr.ubx.poo.td.World;
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
        int length = Math.max(Math.abs(target.x()-getPosition().x()), Math.abs(target.y()-getPosition().y()))*2;
        if (length % 2 == 0) {
            length += 1;
        } else {
            length += 2;
        }
        

        Position[] Movement_Array = new Position[length];
        Movement_Array[0] = new Position(actualX, actualY);
        int i = 1;
        for (; (actualX != target.x() || actualY != target.y()) && i < length; i+=2) {
            if (target.x() != actualX) {
                if (actualX < target.x()) {
                    actualX++;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualX--;
                        break;
                    }
                } else if (actualX > target.x()) {
                    actualX--;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualX++;
                        break;
                    }
                }
                Movement_Array[i] = new Position(actualX, actualY);
            } else {
                Movement_Array[i] = new Position(actualX, actualY);
            }

            if (target.y() != actualY) {
                if (actualY < target.y()) {
                    actualY++;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualY--;
                        break;
                    }
                } else if (actualY > target.y()) {
                    actualY--;
                    if (World.get(new Position(actualX, actualY)) == World.ROCK) {
                        actualY++;
                        break;
                    }
                }
                Movement_Array[i+1] = new Position(actualX, actualY);
            } else {
                Movement_Array[i+1] = new Position(actualX, actualY);
            }
        }

        for (; i < length; i++) {
            Movement_Array[i] = new Position(actualX, actualY);
        }

        return Movement_Array;
    }
}
