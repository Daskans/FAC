package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.scene.image.ImageView;

public class SpriteDrone extends SpriteVehicle{
    
    public SpriteDrone(Drone drone) {
        super(drone, new ImageView(ImageResource.imageDrone));
    }

}
