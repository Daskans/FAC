package td3.Decorators;

import td3.Product;

public class VATProductDecorator extends ProductDecorator {
    private double vat;
    public VATProductDecorator(Product decoratedProduct, double vat) {
        super(decoratedProduct);
        this.vat = vat;
    }
}
