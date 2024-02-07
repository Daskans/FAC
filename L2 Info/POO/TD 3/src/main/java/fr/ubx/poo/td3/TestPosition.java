package fr.ubx.poo.td3;

public class TestPosition {

    public static void main(String[] args) {
        Position p1 = new Position(1, 1);
        Position p2 = new Position(1, 1);
        Position p3 = new Position(1, 2);
        Position p4 = new Position(2, 1);

        if (p1.equals(p2) && !(p3.equals(p4))) {
            System.out.println("The solution to question 2 is correct.");
        } else {
            System.out.println("The solution to question 2 is not correct.");
        }
    }


}
