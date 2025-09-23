package src.java.product;

import java.util.HashMap;
import java.util.Map;

public class Catalog {
    private static Catalog instance = new Catalog();
    private Map<Product, Integer> catalog;

    public Catalog() {
        catalog = new HashMap<>();
    }

    public static Catalog getInstance() {
        return instance;
    }

    public void addProduct(Product product, int quantity) {
        if (catalog.containsKey(product)) {
            catalog.put(product, catalog.get(product) + quantity);
        } else {
            catalog.put(product, quantity);
        }
    }

    public int RemoveProduct(Product product, int quantity) {
        if (catalog.containsKey(product)) {
            int current = catalog.get(product);
            int updated = current - quantity;
            if (updated > 0) {
                catalog.put(product, updated);
                return updated;
            } else if (updated == 0) {
                catalog.put(product, updated);
                catalog.remove(product);
                return updated;
            } else {
                catalog.remove(product);
                return updated;
            }
        }
        System.err.println("ERROR : Product does not exists");
        return 0;
    }

}
