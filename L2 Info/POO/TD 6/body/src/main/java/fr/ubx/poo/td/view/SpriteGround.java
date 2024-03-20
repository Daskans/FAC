package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.scene.image.ImageView;

public class SpriteGround extends SpriteDecor{
        
    public SpriteGround(Position position) {
        super(position, new ImageView(ImageResource.imageGround));
    }

}