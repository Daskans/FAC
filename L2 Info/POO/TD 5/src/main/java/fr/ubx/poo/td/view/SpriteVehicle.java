package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.animation.PathTransition;
import javafx.scene.image.ImageView;
import javafx.scene.image.Image;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

abstract public class SpriteVehicle extends Sprite {
    private Vehicle vehicle;

    public SpriteVehicle(Vehicle vehicle, ImageView img) {
        super(img, vehicle.getPosition());
        this.vehicle = vehicle;
    }
    
    public void animateMove(Position target) {
        // Make the path movement
        Position[] positionPath = vehicle.getPathTo(target);
        vehicle.isMoving = true;
        
        if (positionPath == null) {
            updateLocation(target);
            vehicle.move(target);
        } else {
            Path path = new Path();

            path.getElements().add(new MoveTo(vehicle.getPosition().x() * ImageResource.size + ImageResource.size / 2,
                    vehicle.getPosition().y() * ImageResource.size + ImageResource.size / 2));
            for (Position pos : positionPath) {
                path.getElements().add(new LineTo(pos.x() * ImageResource.size + ImageResource.size / 2, pos.y() * ImageResource.size + ImageResource.size / 2));
            }

            PathTransition ptr = new PathTransition();
            ptr.setDuration(Duration.millis(200 * vehicle.distance(target)));
            ptr.setPath(path);
            ptr.setNode(getImg());

            ptr.setOnFinished(e -> {
                vehicle.move(target);
            });
            ptr.play();

        }
        vehicle.isMoving = false;
    }
}
