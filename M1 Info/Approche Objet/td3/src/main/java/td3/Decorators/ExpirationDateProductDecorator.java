package td3.Decorators;


import java.util.Calendar;

import td3.CostumerProduct;
import td3.Product;

public class ExpirationDateProductDecorator extends ProductDecorator implements Deadline {
    
    Calendar deadline;

    public ExpirationDateProductDecorator(Product decoratedProduct, Calendar deadline) {
        super(decoratedProduct);
        this.deadline = deadline;
    }

    public boolean isExpired(CostumerProduct product) {
        return false;
    }
}
