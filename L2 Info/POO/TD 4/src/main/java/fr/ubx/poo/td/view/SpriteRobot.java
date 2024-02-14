package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.scene.image.ImageView;

public class SpriteRobot extends SpriteVehicle{
    
    public SpriteRobot(Robot robot) {
        super(robot, new ImageView(ImageResource.imageRobot));
    }
}
