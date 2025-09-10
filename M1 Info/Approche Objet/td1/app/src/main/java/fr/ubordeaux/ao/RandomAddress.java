package fr.ubordeaux.ao;

import java.util.Random;

public class RandomAddress {

    private static final String[] streetNames = {
            "Rue de la Paix", "Avenue des Champs-Élysées", "Boulevard Saint-Germain", "Rue Victor Hugo",
            "Avenue de l'Opéra",
            "Rue de Rivoli", "Boulevard Haussmann", "Rue de la République", "Rue du Faubourg Saint-Honoré",
            "Rue de la Gare"
    };

    private static Random random = new Random();

    private int streetNumber;

    private String streerName;

    private Town town;

    public int getStreetNumber() {
        return streetNumber;
    }

    public String getStreetName() {
        return streerName;
    }

    public Town getTown() {
        return town;
    }

    public RandomAddress() {
        streetNumber = generateStreetNumber();
        streerName = generateStreetName();
        town = generateTown();
    }

    // Méthode pour générer un numéro de rue aléatoire (entre 1 et 999)
    private static int generateStreetNumber() {
        return random.nextInt(999) + 1;
    }

    // Méthode pour générer un nom de rue aléatoire
    private static String generateStreetName() {
        return streetNames[random.nextInt(streetNames.length)];
    }

    // Méthode pour générer une ville aléatoire
    private static Town generateTown() {
        String pair[] = Town.towns[random.nextInt(Town.towns.length)];
        return new Town(pair[0], pair[1]);
    }

}
