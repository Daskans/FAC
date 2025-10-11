package td3.Decorators;

import td3.Product;

public abstract class ProductDecorator implements Product{
    private Product decoratedProduct;
    
    public ProductDecorator(Product decoratedProduct) {
        this.decoratedProduct = decoratedProduct;
    }

    @Override
    public String getName() {
        return decoratedProduct.getName();
    }

    @Override
    public double getPriceExcludingVAT() {
        return decoratedProduct.getPriceExcludingVAT();
    }

    @Override
    public final double getPriceIncludingVAT() {
        return getPriceExcludingVAT() * (1 + getVATAmount());
    }

    @Override
    public double getVATAmount() {
        return decoratedProduct.getVATAmount();
    }
}
