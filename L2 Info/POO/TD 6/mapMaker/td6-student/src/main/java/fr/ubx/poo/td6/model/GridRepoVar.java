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

    @Override
    public Grid load(String string) {
        /*  Crée une nouvelle instance de la classe Grid et initialise les champs de l'objet avec les informations de sample1.
            Retourn le nouvel objet.
         */
        Grid new_grid = new Grid(9,9 );
        for(int i = 0 ;i<new_grid.getHeight();i++){
            for(int j = 0;j<new_grid.getWidth();j++){
                new_grid.set(i, j, sample1[i][j]);
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
}
