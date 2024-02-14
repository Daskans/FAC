package fr.ubx.poo.td;

import fr.ubx.poo.td.view.*;
import fr.ubx.poo.td.model.*;
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
        SpriteVehicle[] spriteVehiclesList = {spriteRobot1, spriteDrone1, spriteRobot2};

        // Create the decor
        SpriteRock spriteRock1 = new SpriteRock(new Position(14, 16));
        SpriteRock spriteRock2 = new SpriteRock(new Position(8, 4));
        SpriteRock spriteRock3 = new SpriteRock(new Position(10, 8));
        SpriteRock spriteRock4 = new SpriteRock(new Position(1, 2));
        SpriteRock spriteRock5 = new SpriteRock(new Position(3, 5));
        SpriteRock spriteRock6 = new SpriteRock(new Position(15, 2));
        SpriteRock spriteRock7 = new SpriteRock(new Position(17, 5));
        SpriteRock spriteRock8 = new SpriteRock(new Position(4, 18));
        SpriteRock spriteRock9 = new SpriteRock(new Position(6, 15));
        SpriteRock spriteRock10 = new SpriteRock(new Position(18, 12));

        SpriteDust spriteDust1 = new SpriteDust(new Position(5, 5));
        SpriteDust spriteDust2 = new SpriteDust(new Position(7, 4));
        SpriteDust spriteDust3 = new SpriteDust(new Position(9, 9));
        SpriteDust spriteDust4 = new SpriteDust(new Position(11, 3));
        SpriteDust spriteDust5 = new SpriteDust(new Position(13, 7));
        SpriteDust spriteDust6 = new SpriteDust(new Position(2, 11));
        SpriteDust spriteDust7 = new SpriteDust(new Position(14, 6));
        SpriteDust spriteDust8 = new SpriteDust(new Position(16, 3));
        SpriteDust spriteDust9 = new SpriteDust(new Position(3, 17));
        SpriteDust spriteDust10 = new SpriteDust(new Position(17, 14));

        SpriteDecor[] decorRocks = {spriteRock1, spriteRock2, spriteRock3, spriteRock4, spriteRock5, spriteRock6, spriteRock7, spriteRock8, spriteRock9, spriteRock10};
        SpriteDecor[] decorDusts = {spriteDust1, spriteDust2, spriteDust3, spriteDust4, spriteDust5, spriteDust6, spriteDust7, spriteDust8, spriteDust9, spriteDust10};
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
                        spriteVehiclesList[i].animateMove(target);
                    }
                }
            }
        });
        for (int i = 0; i < vehicles.length; i++) {
            view.getPane().getChildren().addAll(spriteVehiclesList[i].getImg());
        }
        for (int i = 0; i < decorRocks.length; i++) {
            view.getPane().getChildren().addAll(decorRocks[i].getImg());
        }
        for (int i = 0; i < decorDusts.length; i++) {
            view.getPane().getChildren().addAll(decorDusts[i].getImg());
        }
    }
    
    public static void main(String[] args) { 
        launch(); 
    }
}