public class Position {

    int x = 0;
    int y = 0;

    Position(int x, int y) {
        this.x = x;
        this.y = y;
    }

    void showPosition() {
        System.out.println("(" + x + "," + y + ")");
    }

    void displacement(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void displacement(int delta) {
        x += delta;
        y += delta;
    }

    double distance(Position target) {
        return Math.sqrt(Math.pow((target.x - x), 2)+Math.pow((target.y - y), 2));
    }
}
