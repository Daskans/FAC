package fr.ubx.poo.td;

import fr.ubx.poo.td.model.*;
import fr.ubx.poo.td.view.*;


public class World {
    public static final int EMPTY = 0;
    public static final int ROCK  = 1;
    public static final int DUST  = 2;

    private static int[][] grid;
    
    public World(int width, int height, int percentageRock, int percentageDust) {
        grid = new int[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                grid[i][j] = EMPTY;
            }
        }
        if (percentageDust != 0) {
            for (int i = 0; i < (width*height)*percentageDust/100; i++) {
                Position position = Position.random(width, height);
                grid[position.x()][position.y()] = DUST;
            }
        }
        if (percentageRock != 0) {
            for (int i = 0; i < (width*height)*percentageRock/100; i++) {
                Position position = Position.random(width, height);
                grid[position.x()][position.y()] = ROCK;
            }
        }
    }

    public static int get(Position position) {
        return grid[position.x()][position.y()];
    }

    public void set(Position position, int value) {
        grid[position.x()][position.y()] = value;
    }
}
