package fr.ubx.poo.td6.model;

import fr.ubx.poo.td6.model.*;
import fr.ubx.poo.td6.model.Entity;
import fr.ubx.poo.td6.model.GridRepo;
import java.lang.reflect.Field;

import static fr.ubx.poo.td6.model.Entity.*;

public class GridRepoVar implements GridRepo {

    private final Entity[][] sample1 = {
            {GROUND, GROUND, GROUND, GROUND, DUST, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, DUST, GROUND, GROUND},
            {GROUND, GROUND, ROCK, CRACK, GROUND, GROUND, BIGROCK, GROUND, GROUND},
            {GROUND, ROCK, GROUND, ROCK, GROUND, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, CRACK, GROUND},
            {GROUND, DUST, GROUND, DUST, GROUND, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, CRACK, GROUND, DUST, BIGROCK, GROUND, GROUND},
            {GROUND, ROCK, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
    };
    private final Entity[][] sample2 = {
            {GROUND, ROCK, DUST, ROCK, GROUND},
            {GROUND, CRACK, BIGROCK, CRACK, DUST},
            {GROUND, CRACK, CRACK, GROUND, BIGROCK},
            {ROCK, DUST, DUST, GROUND, DUST}
    };


    @Override
    public Grid load(String string) {
        /*  Crée une nouvelle instance de la classe Grid et initialise les champs de l'objet avec les informations de sample1.
            Retourn le nouvel objet.
         */
        Entity[][] entities = getEntities(string);
        if (entities == null)
            return null;
        int height = entities.length;
        int width = entities[0].length;
        Grid new_grid = new Grid(width, height);
        for(int i = 0 ;i < height;i++){
            for(int j = 0;j < width;j++){
                System.out.printf("%d %d %d %d\n", i, j, height, width);
                new_grid.set(j, i, entities[i][j]);
            }
        }
        return new_grid;
    }

    @Override
    public String export(Grid grid) {
        /*  Retourne sous forme de chaîne de caractères la déclaration Java correspondant aux tableau d'entités de l'objet grid.
            Le résultat produit doit être de la forme: private final Entity[][] sample1 = {....};
            Le code produit peut être utilisé pour remplacer la déclaration de sample1 plus haut.
        */
        return null;
    }
    private Entity[][] getEntities(String name) {
        try {
            Field field = this.getClass().getDeclaredField(name);
            return (Entity[][]) field.get(this);
        } catch (IllegalAccessException e) {
            return null;
        } catch (NoSuchFieldException e) {
            return null;
        }
    }

}
