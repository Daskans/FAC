package td3.Decorators;

import td3.Product;

public class PackageProductDecorator extends ProductDecorator{

    int number;

    public PackageProductDecorator(Product decoratedProduct, int number) {
        super(decoratedProduct);
        this.number = number;
    }
}
