package fr.ubx.poo.td6.model;

public class GridException {
    public static void checkCharacter(char c) {
        if (c != 'R' && c != 'B' && c != 'G' && c != 'C' && c != 'E' && c != 'D' && c != 'x') {
            throw new IllegalArgumentException("Invalid character");
        }
    }

    public static void checkGridWidth(String string) {
        String[] entityString = string.split("x");
        int width = entityString[0].length();
        for (int i = 1; i < entityString.length; i++) {
            if (entityString[i].length() != width) {
                throw new IllegalArgumentException("Invalid grid width");
            }
        }
    }

    public static void checkEOLLocation(String string) {
        if (string.charAt(string.length() - 1) != 'x' ) {
            throw new IllegalArgumentException("Invalid EOL location");
        }
    }
}
