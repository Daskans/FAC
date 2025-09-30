package src.java.product;

import java.util.HashMap;
import java.util.Map;

public class Basket {
    Map<Product, Integer> basket;

    public Basket() {
        basket = new HashMap<>();
    }

    public void addProduct(Product product, int quantity) {
        Catalog catalog = Catalog.getInstance();
        int remaining = catalog.removeProduct(product, quantity);
        if (remaining >= 0) {
            basket.put(product, quantity);
        } else {
            System.err.println("ERROR : Not enough quantity for product : " + product.getName() + "(" + remaining + " remaining)");
        }
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Basket contents:\n");
        for (Map.Entry<Product, Integer> entry : basket.entrySet()) {
            sb.append(entry.getKey().getName())
            .append(" x")
            .append(entry.getValue())
            .append("\n");
                
        }
        return sb.toString();
    }
}
