package fr.ubx.poo.td.view;

import fr.ubx.poo.td.*;
import fr.ubx.poo.td.model.*;

public class DecorFactory {
    public static SpriteDecor create(Position position, int kind) {
        switch (kind) {
            case World.DUST:
                return new SpriteDust(position);
            case World.ROCK:
                return new SpriteRock(position);
            default:
                return null;
        }
    }
}
