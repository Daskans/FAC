package fr.ubx.poo.td6.model;

public class Grid {

    private final int width;
    private final int height;
    private final Entity[][] grid;


    public Grid(int width, int height) {
        this.width = width;
        this.height = height;
        this.grid = new Entity[height][width];
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }


    public Entity get(int i, int j) {
        return grid[j][i];
    }

    public void set(int i, int j, Entity entity) {
        grid[j][i] = entity;
    }

}
