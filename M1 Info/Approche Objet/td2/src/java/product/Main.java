package src.java.product;

public class Main {
    public static void main(String[] args) {
        Catalog catalog = Catalog.getInstance();
        Basket basket = new Basket();
        Product product1 = new Product("apple", 10f, 20f);
        Product product2 = new Product("apple", 10f, 20f);
        catalog.addProduct(product1, 15);
        catalog.addProduct(product2, 10);
        System.out.println(catalog.toString());
        basket.addProduct(product1, 3);
        System.out.println(catalog.toString());
        System.out.println(basket.toString());
        System.out.println("DONE !");
    }
}
