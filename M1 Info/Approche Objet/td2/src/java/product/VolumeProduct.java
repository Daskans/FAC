package src.java.product;

public class VolumeProduct extends Product{

    private float volume;

    public VolumeProduct(String name, float price, float vat) {
        super(name, price, vat);
    }

    @Override
    public float getPriceExcludingVAT() {
        return super.getPriceExcludingVAT() * volume;
    }

    @Override
    public float getPriceIncludingVAT() {
        return super.getPriceIncludingVAT() * volume;
    }
}
