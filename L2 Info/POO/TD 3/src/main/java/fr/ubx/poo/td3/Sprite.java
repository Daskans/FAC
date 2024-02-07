package fr.ubx.poo.td3;

import javafx.animation.PathTransition;
import javafx.scene.image.ImageView;
import javafx.scene.image.Image;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

public class Sprite {
    private Vehicle vehicle;
    private ImageView img;

    public Sprite(Vehicle vehicle, ImageView img) {
        this.vehicle = vehicle;
        this.img = img;
        updateLocation(vehicle.position);
    }

    private void updateLocation(Position position) {
        img.setX(position.x * ImageResource.size);
        img.setY(position.y * ImageResource.size);
    }

    public ImageView getImg() {
        return img;
    }

    public void animateMove(Position target) {
        // Make the path movement
        Position[] positionPath = vehicle.getPathTo(target);

        if (positionPath == null) {
            updateLocation(target);
            vehicle.move(target);
        } else {
            Path path = new Path();

            path.getElements().add(new MoveTo(vehicle.position.getX() * ImageResource.size + ImageResource.size / 2,
                    vehicle.position.getY() * ImageResource.size + ImageResource.size / 2));
            for (Position pos : positionPath) {
                path.getElements().add(new LineTo(pos.x * ImageResource.size + ImageResource.size / 2, pos.y * ImageResource.size + ImageResource.size / 2));
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
    }
}
