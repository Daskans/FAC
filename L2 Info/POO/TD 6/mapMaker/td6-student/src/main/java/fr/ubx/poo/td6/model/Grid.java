package fr.ubx.poo.td6.model;

public class Grid {

    private final int height;
    private final int width;
    private final Entity[][] grid;


    public Grid(int width, int height) {
        this.height = height;
        this.width = width;
        this.grid = new Entity[height][width];
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }


    public Entity get(int width, int height) {
        return grid[height][width];
    }

    public void set(int width, int height, Entity entity) {
        grid[height][width] = entity;
    }

}
