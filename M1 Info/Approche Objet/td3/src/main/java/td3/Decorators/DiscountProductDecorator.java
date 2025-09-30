package td3.Decorators;

import td3.Product;

public class DiscountProductDecorator extends ProductDecorator {
    // ...implementation...
    public DiscountProductDecorator(Product decoratedProduct, double discountRate) {
        super(decoratedProduct);
        // ...store discountRate...
    }
}
