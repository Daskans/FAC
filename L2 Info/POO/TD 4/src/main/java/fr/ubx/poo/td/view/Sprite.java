package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.animation.PathTransition;
import javafx.scene.image.ImageView;
import javafx.scene.image.Image;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

public class Sprite {
    private ImageView img;

    public Sprite(ImageView img, Position position) {
        this.img = img;
        updateLocation(position);
    }

    public ImageView getImg() {
        return img;
    }

    public void updateLocation(Position position) {
        getImg().setX(position.x() * ImageResource.size);
        getImg().setY(position.y() * ImageResource.size);
    }
    
}