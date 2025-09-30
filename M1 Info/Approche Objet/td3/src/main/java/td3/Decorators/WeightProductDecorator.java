package td3.Decorators;

import td3.Product;

public class WeightProductDecorator extends ProductDecorator {
    
    private double weight;
    
    public WeightProductDecorator(Product decoratedProduct, double weight) {
        super(decoratedProduct);
    }

    @Override
    public double getPriceExcludingVAT() {
        return super.getPriceExcludingVAT() * weight;
    }
}
