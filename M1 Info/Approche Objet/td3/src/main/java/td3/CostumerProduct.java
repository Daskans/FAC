package td3;

import java.util.UUID;

public class CostumerProduct implements Product {

        private String name;
        private double price;
        private double vat;
        private UUID id;

        public CostumerProduct(String name, double price, double vat) {
            this.name = name;
            this.price = price;
            this.vat = vat;
        }

        public String getName() {
            return name;
        }

        public double getPriceExcludingVAT() {
            return price;
        }

        @Override
        public double getPriceIncludingVAT() {
            // TODO Auto-generated method stub
            throw new UnsupportedOperationException("Unimplemented method 'getPriceIncludingVAT'");
        }

        @Override
        public final double getVATAmount() {
            return vat;
        }

        

}
