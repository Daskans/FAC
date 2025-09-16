package fr.ubordeaux.ao;

public class Town {

    public static final String[][] towns = {
        { "Paris", "75000" },
        { "Lyon", "69000" },
        { "Marseille", "13000" },
        { "Toulouse", "31000" },
        { "Nice", "06000" },
        { "Nantes", "44000" },
        { "Strasbourg", "67000" },
        { "Montpellier", "34000" },
        { "Bordeaux", "33000" },
        { "Lille", "59000" } };

    private String name;
    private int zipcode;

    public Town(String name, int zipcode) {
        this.name = name;
        for (String[] town : towns) {
            if (town[0].equals(name)) {
                if (town[1].equals(zipcode)) {
                    this.zipcode = zipcode;
                    break;
                } else {
                    throw new IllegalArgumentException("illegal zipcode : had "+zipcode+", should have "+town[1]);
                }
            }
        }
    }

    // Constructeur qui prend un code postal en chaîne de caractères
    public Town(String name, String zipcode) {
        this.name = name;
        this.zipcode = Integer.parseInt(zipcode); // Conversion String -> int
    }

    public String getName() {
        return name;
    }

    public int getZipCode() {
        return zipcode;
    }

    @Override
    public String toString() {
        return name + " - " + zipcode;
    }

}