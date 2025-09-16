package fr.ubordeaux.ao;

public class Address {

    private int number;
    private String street;
    private Town town;

    public Address(int number, String street, Town town) {
        this.number = number;
        this.street = street;
        this.town = town;
    }

    public int getNumber() {
        return number;
    }

    public String getStreet() {
        return street;
    }

    public Town getTown() {
        return town;
    }

    @Override
    public String toString() {
        return number + ", " + street + ", " + town.toString();
    }

}