package fr.ubx.poo.td3;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage stage)  {

        // Create the robot curiosity
        Position positionRobot1 = new Position(4, 4);
        Robot robot1 = new Robot("curiosity", positionRobot1, 200, 2);
        SpriteRobot spriteRobot1 = new SpriteRobot(robot1);

        // Create the drone Ingenuity
        Position positionDrone1 = new Position(8, 9);
        Drone drone1 = new Drone("ingenuity", positionDrone1, 100, 1);
        SpriteDrone spriteDrone1 = new SpriteDrone(drone1);

        // Create the robot Opportunity
        Position positionRobot2 = new Position(12, 4);
        Robot robot2 = new Robot("opportunity", positionRobot2, 200, 2);
        SpriteRobot spriteRobot2 = new SpriteRobot(robot2);

        // Create the vehicle list
        Vehicle[] vehicles = {robot1, drone1, robot2};
        Sprite[] sprites = {spriteRobot1, spriteDrone1, spriteRobot2};
        // Display the window
        View view = new View(20, 20);
        stage.setTitle("POO");
        stage.setScene(view.getPane().getScene());
        stage.show();
        view.getPane().setOnMouseClicked(e -> {
            Position target = view.getPosition(e);
            for (int i = 0; i < vehicles.length; i++) {
                if (!(vehicles[i].getPosition().equals(target))) {
                    if (vehicles[i].canMove(target)) {
                        sprites[i].animateMove(target);
                    }
                }
            }
        });
        for (int i = 0; i < vehicles.length; i++) {
            view.getPane().getChildren().addAll(sprites[i].getImg());
        }
    }
    
    public static void main(String[] args) { 
        launch(); 
    }
}