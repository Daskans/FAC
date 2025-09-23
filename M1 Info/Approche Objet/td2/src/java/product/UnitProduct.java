package src.java.product;

public class UnitProduct extends Product{
    private int unit;
    public UnitProduct(String name, float price, float vat, int unit) {
        super(name, price, vat);
        this.unit = unit;
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
