package fr.ubx.poo.td6.model;

public enum Entity {
    ROCK('R'),
    BIGROCK('B'),
    GROUND('G'),
    CRACK('C'),
    ENERGY('E'),
    DUST('D');

    private final char code;

    Entity(char c) {
        this.code = c;
    }

    public char getCode() { return this.code; }

    public static Entity fromCode(char c) {
        for (Entity entity : values()) {
            if (entity.getCode() == c)
                return entity;
        }
        return null;
    }
}
