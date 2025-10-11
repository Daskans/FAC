package td3.Decorators;

import td3.Product;

public class VolumeProductDecorator extends ProductDecorator {
    
    private double volume;

    public VolumeProductDecorator(Product decoratedProduct, double volume) {
        super(decoratedProduct);
        this.volume = volume;
    }

    @Override
    public double getPriceExcludingVAT() {
        return super.getPriceExcludingVAT() * volume;
    }
}
