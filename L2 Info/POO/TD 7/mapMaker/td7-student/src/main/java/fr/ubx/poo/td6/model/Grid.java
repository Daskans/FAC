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

    public Graph<Position> getGraph() {
        Graph<Position> graph = new Graph<>();
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                graph.addNode(new Position(i, j));
            }
        }
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Node<Position> node = new Node<>(new Position(i, j));
                if (get(i,j).isAccessible()) {
                    if (i > 0 && get(i,j).isAccessible()) {
                        graph.getNode(new Position(i, j)).addEdge(graph.getNode(new Position(i-1, j)));
                    } if (i < width - 1 && get(i,j).isAccessible()) {
                        graph.getNode(new Position(i, j)).addEdge(graph.getNode(new Position(i+1, j)));
                    } if (j > 0 && get(i,j).isAccessible()) {
                        graph.getNode(new Position(i, j)).addEdge(graph.getNode(new Position(i, j-1)));
                    } if (j < height - 1 && get(i,j).isAccessible()) {
                        graph.getNode(new Position(i, j)).addEdge(graph.getNode(new Position(i, j+1)));
                    }
                }
            }
        }
        return graph;
    }



}
