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

    
}
