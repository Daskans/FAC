package td3.Decorators;

import td3.Product;

public class FidelityOfferProductDecorator extends ProductDecorator {
    // ...implementation...
    public FidelityOfferProductDecorator(Product decoratedProduct) {
        super(decoratedProduct);
    }
}
