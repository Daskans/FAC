package src.java.product;

public class Product {
    private final String name;
    private final float price;
    private final float vat;

    public Product(String name, float price, float vat) {
        this.name = name;
        this.price = price;
        this.vat = vat;
    }

    public String getName() {
        return name;
    }

    public float getPriceExcludingVAT() {
        return price;
    }

    public float getVATAmount() {
        return vat;
    }

    public float getPriceIncludingVAT() {
        return getPriceExcludingVAT() + (getPriceExcludingVAT() * (getVATAmount() / 100));
    }

    public String toString() {
        String toString = "Product : " + getName() + 
                        " | price : " + getPriceExcludingVAT() + 
                        " | VAT : " + getVATAmount() +
                        " | price with vat : " + getPriceIncludingVAT();
        return toString;
    }
}
