package fr.ubx.poo.td;

import fr.ubx.poo.td.view.*;
import fr.ubx.poo.td.model.*;
import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage stage)  {

        
        // Display the window
        int width = 25;
        int height = 25;
        World world = new World(width, height, 10, 20);
        View view = new View(width, height);
        stage.setTitle("POO");
        stage.setScene(view.getPane().getScene());
        stage.show();


        // Place the ground and the decor
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Position position = new Position(i, j);
                SpriteDecor spriteDecor = DecorFactory.create(position, World.get(position));
                view.getPane().getChildren().add(new SpriteGround(position).getImg());
                if (spriteDecor != null) {
                    view.getPane().getChildren().add(spriteDecor.getImg());
                }
            }
        }

        // Create the robot curiosity
        Position positionRobot1 = new Position(4, 4);
        Robot robot1 = new Robot("curiosity", positionRobot1, 2000, 2);
        SpriteRobot spriteRobot1 = new SpriteRobot(robot1);
        
        // Create the drone Ingenuity
        Position positionDrone1 = new Position(8, 9);
        Drone drone1 = new Drone("ingenuity", positionDrone1, 100, 1);
        SpriteDrone spriteDrone1 = new SpriteDrone(drone1);
        
        // Create the robot Opportunity
        /*
        Position positionRobot2 = new Position(12, 4);
        Robot robot2 = new Robot("opportunity", positionRobot2, 200, 2);
        SpriteRobot spriteRobot2 = new SpriteRobot(robot2);*/
        
        // Create the vehicle list
        Vehicle[] vehicles = {robot1, drone1};
        SpriteVehicle[] spriteVehiclesList = {spriteRobot1, spriteDrone1};

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
    }
    
    public static void main(String[] args) { 
        launch(); 
    }
}