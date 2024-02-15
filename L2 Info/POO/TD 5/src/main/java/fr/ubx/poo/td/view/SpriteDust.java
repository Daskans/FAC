package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.scene.image.ImageView;

public class SpriteDust extends SpriteDecor{
        
    public SpriteDust(Position position) {
        super(position, new ImageView(ImageResource.imageDust));
    }

}
