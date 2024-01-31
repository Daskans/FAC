package fr.ubx.poo.td2;

public class Position {
    int x;
    int y;

    Position(int x, int y) {
        this.x = x;
        this.y = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    public void translate(int dx, int dy) {
        x += dx;
        y += dy;
    }

    public void translate(int delta) {
        x += delta;
        y += delta;
    }
}
