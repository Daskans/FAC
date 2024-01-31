public class TestPosition {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("ERROR : Incorrect number of argument");
        } else {
            Position pos = new Position(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
            pos.showPosition();
            pos.displacement(1, 2);
            pos.showPosition();
            pos.displacement(1);
            pos.showPosition();
            Position pos2 = new Position(3, 3);
            pos2.showPosition();
        }
    }
}
