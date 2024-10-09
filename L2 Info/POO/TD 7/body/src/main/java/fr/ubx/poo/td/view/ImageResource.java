package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.scene.image.Image;

public class ImageResource {
    public static final int size = 40;
    public static final Image imageRobot = loadImage("robot.png");
    public static final Image imageDrone = loadImage("drone.png");
    public static final Image imageDust = loadImage("dust2.png");
    public static final Image imageGround = loadImage("ground.png");
    public static final Image imageRock = loadImage("rock.png");

    private static Image loadImage(String file) {
        return new Image(ImageResource.class.getResourceAsStream("/images/" + file));
    }
}

