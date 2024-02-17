package fr.ubx.poo.td2;

public class TestRobot {
    public static void main(String[] args){
        // Run the test cases
        if (testTranslateInitialPosition()) {
            System.out.println("The solution to question 3 is correct.");
        } else {
            System.out.println("The solution to question 3 is not correct.");
        }
        if (testGetPosition()) {
            System.out.println("The solution to question 5 is correct.");
        } else {
            System.out.println("The solution to question 5 is not correct.");
        }
    }

    private static boolean testTranslateInitialPosition(){
        Position initialPosition = new Position(4,4);
        Robot robot = new Robot("Curiosity",initialPosition, 10, 10);
        initialPosition.translate(10,10);
        return robot.getPosition().getX() != initialPosition.getX() && 
            robot.getPosition().getY() != initialPosition.getY();
    }
    
    private static boolean testGetPosition(){
        Position initialPosition = new Position(4,4);
        Robot robot = new Robot("Curiosity",initialPosition, 10, 10);
        Position nextPosition = robot.getPosition();
        nextPosition.translate(10,10);
        return robot.getPosition() != nextPosition;
    }
}