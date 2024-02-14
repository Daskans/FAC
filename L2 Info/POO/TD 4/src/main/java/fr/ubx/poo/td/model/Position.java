package fr.ubx.poo.td.model;

import fr.ubx.poo.td.view.*;

public final record Position(int x, int y){

    public Position translate(int dx, int dy) {
        return new Position(x + dx, y + dy);
    }

    public Position translate(int delta) {
        return new Position(x + delta, y + delta);
    }
}
