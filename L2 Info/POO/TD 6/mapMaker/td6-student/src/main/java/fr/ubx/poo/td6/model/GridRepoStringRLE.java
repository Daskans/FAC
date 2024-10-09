package fr.ubx.poo.td6.model;

import fr.ubx.poo.td6.model.*;
import fr.ubx.poo.td6.model.Entity;
import fr.ubx.poo.td6.model.GridRepo;
import fr.ubx.poo.td6.model.GridRepoString;
import java.lang.reflect.Field;
import java.util.Arrays;
import java.io.*;


public class GridRepoStringRLE implements GridRepo{
    final char EOL = 'x';
    final String sample1 = "GGGGDGGGGxGGGGGGDGGxGGRCGGBGGxGRGRGGGGGxGGGGGGGGGxGGGGGGGCGxGDGDGGGGGxGGGCGDBGGxGRGGGGGGGx";

    @Override
    public Grid load(String string) {
        /*  Crée une nouvelle instance de la classe Grid et initialise les champs de l'objet avec les informations de sample1.
            Retourn le nouvel objet.
         */
        char[] part = string.toCharArray();
        string = "";
        for (int i = 0; i < part.length; i++) {
            if (i>0 && (part[i] > '1' && part[i] <= '9')) {
                for (int j = 0; j < part[i] - '0' - 1; j++) {
                    string += part[i-1];

                }
            } else {
                string += part[i];
            }
        }
        System.out.println(string);
        GridException.checkGridWidth(string);
        GridException.checkEOLLocation(string);
        part = string.toCharArray();
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
        String compressedString = "";
        for (int i = 0; i < string.length(); i++) {
            int count = 1;
            while (i < string.length() - 1 && string.charAt(i) == string.charAt(i + 1)) {
                count++;
                i++;
            }
            compressedString += string.charAt(i);
            if (count > 1) {compressedString += count;}
        }

        return compressedString;
    }

    public Grid create(int height, int width) {
        Grid new_grid = new Grid(width, height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                new_grid.set(j, i, Entity.GROUND);
            }
        }
        return new_grid;
    }


}
