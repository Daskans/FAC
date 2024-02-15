package fr.ubx.poo.td.model;

import java.util.Random;

import fr.ubx.poo.td.view.*;

public final record Position(int x, int y){

    public Position translate(int dx, int dy) {
        return new Position(x + dx, y + dy);
    }

    public Position translate(int delta) {
        return new Position(x + delta, y + delta);
    }

    public random(int width, int height) {
        Random random = new Random();
        int random_width = random.nextInt(width);
        int random_height = random.nextInt(height);
        return new Position(random_width, random_height);
    }
}
