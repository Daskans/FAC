package src.java.product;

public class ServiceProduct extends Product{
    private float unit;
    public ServiceProduct(String name, float price, float vat) {
        super(name, price, vat);
    }

    @Override
    public float getPriceExcludingVAT() {
        return super.getPriceExcludingVAT() * unit;
    }

    @Override
    public float getPriceIncludingVAT() {
        return super.getPriceIncludingVAT() * unit;
    }
}
