package fr.ubordeaux.ao;

public class Main {

    private static final int MAX = 100;

    public static void main(String[] args) {
        ContactSet contactSet = new ContactSet();

        for (int i = 0; i < MAX; i++) {

            RandomAddress randomAddress = new RandomAddress();
            Address address = new Address(randomAddress.getStreetNumber(), randomAddress.getStreetName(),
                    randomAddress.getTown());
            Contact newContact = new Contact("John", "Do", address);
            contactSet.addContact(newContact);
        }
        System.out.println(contactSet.size() + " contacts created. !");
        System.out.println(contactSet);

    }
}