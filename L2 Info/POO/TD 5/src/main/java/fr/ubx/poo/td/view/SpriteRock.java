package fr.ubx.poo.td.view;

import fr.ubx.poo.td.model.*;
import javafx.scene.image.ImageView;

public class SpriteRock extends SpriteDecor{
    
    public SpriteRock(Position position) {
        super(position, new ImageView(ImageResource.imageRock));
    }

}
