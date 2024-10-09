package fr.ubx.poo.td6.model;

import fr.ubx.poo.td6.model.*;
import fr.ubx.poo.td6.model.Entity;
import fr.ubx.poo.td6.model.GridRepo;
import fr.ubx.poo.td6.model.GridRepoString;
import java.lang.reflect.Field;
import java.util.Arrays;

public class GridRepoString implements GridRepo{
    final char EOL = 'x';
    final String sample1 = "GGGGDGGGGxGGGGGGDGGxGGRCGGBGGxGRGRGGGGGxGGGGGGGGGxGGGGGGGCGxGDGDGGGGGxGGGCGDBGGxGRGGGGGGGx";

    @Override
    public Grid load(String string) {
        /*  Crée une nouvelle instance de la classe Grid et initialise les champs de l'objet avec les informations de sample1.
            Retourn le nouvel objet.
         */
        GridException.checkGridWidth(string);
        GridException.checkEOLLocation(string);
        char[] part = string.toCharArray();
        int len = part.length;
        int width = 0;
        for (int i = 0; i < len; i++) {
            if (part[i] == EOL) {
                break;
            }
            width++;
        }
        int height = len/(width + 1);
        String[] entityString = string.split("x");
        string = String.join("",entityString);
        part = string.toCharArray();
        Grid new_grid = new Grid(width, height);
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                char actualChar = part[j * (width) + i];
                GridException.checkCharacter(actualChar);
                if (actualChar != EOL) {
                    new_grid.set(i, j, Entity.fromCode(actualChar));
                }
            }
        }
        return new_grid;
    }

    @Override
    public String export(Grid grid) {
        String string = "";
        for (int height = 0; height < grid.getHeight(); height++) {
            for (int width = 0; width < grid.getWidth(); width++) {
                string += grid.get(width, height).getCode();
            }
            string += 'x';
        }
        return string;
    }

    public Grid create(int width, int height) {
        Grid new_grid = new Grid(width, height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                new_grid.set(j, i, Entity.GROUND);
            }
        }
        return new_grid;
    }
    

}
