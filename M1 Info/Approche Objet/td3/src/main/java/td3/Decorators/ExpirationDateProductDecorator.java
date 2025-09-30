package td3.Decorators;

import td3.CostumerProduct;
import td3.Product;

public class ExpirationDateProductDecorator extends ProductDecorator implements Deadline {
    // ...implementation...
    public ExpirationDateProductDecorator(Product decoratedProduct) {
        super(decoratedProduct);
    }

    public boolean isExpired(CostumerProduct product) {
        return false;
    }
}
