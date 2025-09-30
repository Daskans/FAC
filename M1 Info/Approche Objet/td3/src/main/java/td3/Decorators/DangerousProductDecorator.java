package td3.Decorators;

import td3.Product;

public class DangerousProductDecorator extends ProductDecorator {
    // ...implementation...
    public DangerousProductDecorator(Product decoratedProduct) {
        super(decoratedProduct);
    }
}
