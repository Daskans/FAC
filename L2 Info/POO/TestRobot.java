public class TestRobot {
    public static void main(String[] args) {
        Robot curiosity = new Robot("Curiosity", new Position(80, 100), 400, 10);
        curiosity.showRobot();
        curiosity.move(new Position(81, 105));
        curiosity.showRobot();
    }
}
