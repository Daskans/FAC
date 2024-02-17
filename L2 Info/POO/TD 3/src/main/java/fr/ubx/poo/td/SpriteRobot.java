package fr.ubx.poo.td;

import javafx.scene.image.ImageView;

public class SpriteRobot extends Sprite{
    
    public SpriteRobot(Robot robot) {
        super(robot, new ImageView(ImageResource.imageRobot));
    }
}
