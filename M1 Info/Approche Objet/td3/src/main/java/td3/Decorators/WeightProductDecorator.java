package td3.Decorators;

import td3.Product;

public class WeightProductDecorator extends ProductDecorator {
    
    private double weight;
    
    public WeightProductDecorator(Product decoratedProduct, double weight) {
        super(decoratedProduct);
        this.weight = weight;
    }

    @Override
    public double getPriceExcludingVAT() {
        return super.getPriceExcludingVAT() * weight;
    }
}
