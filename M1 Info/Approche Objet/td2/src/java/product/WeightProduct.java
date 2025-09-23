package src.java.product;

public class WeightProduct extends Product{

    private float weight;

    public WeightProduct(String name, float price, float vat) {
        super(name, price, vat);
    }

    @Override
    public float getPriceExcludingVAT() {
        return super.getPriceExcludingVAT() * weight;
    }

    @Override
    public float getPriceIncludingVAT() {
        return super.getPriceIncludingVAT() * weight;
    }
}
