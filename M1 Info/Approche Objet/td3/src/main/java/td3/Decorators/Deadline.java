package td3.Decorators;

import td3.CostumerProduct;

public interface Deadline {

    public boolean isExpired(CostumerProduct product);
}
