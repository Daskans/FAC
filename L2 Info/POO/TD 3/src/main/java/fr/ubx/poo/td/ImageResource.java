package fr.ubx.poo.td;


import javafx.scene.image.Image;

public class ImageResource {
    public static final int size = 40;
    public static final Image imageRobot = loadImage("robot.png");
    public static final Image imageDrone = loadImage("drone.png");

    private static Image loadImage(String file) {
        return new Image(ImageResource.class.getResourceAsStream("/images/" + file));
    }
}

