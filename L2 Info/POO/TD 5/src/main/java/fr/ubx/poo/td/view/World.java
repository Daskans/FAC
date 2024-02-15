package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.model.*;

public class World {
    public static final int EMPTY = 0;
    public static final int ROCK  = 1;
    public static final int DUST  = 2;

    private final int[][] grid;
    public final int percentageRock;
    public final int percentageDust;
    
    public World(int width, int height, int percentageRock, int percentageDust) {
        this.grid = new int[height][width];
        this.percentageRock = percentageRock;
        this.percentageDust = percentageDust;
    }

    public int get(Position position) {
        return grid[position.x()][position.y()];
    }

    public void set(Position position, int value) {
        grid[position.x()][position.y()] = value;
    }
}
