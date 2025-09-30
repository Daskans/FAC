package td3;

public interface Product {

    String getName();
    double getPriceExcludingVAT();
    double getPriceIncludingVAT();
    double getVATAmount();
}
