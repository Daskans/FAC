package td3;

import td3.Decorators.*;

public class Main {
    public static void main(String[] args) {
        CostumerProduct product = new CostumerProduct("apple", 1, 0.05);
        VolumeProductDecorator volumeDecorator = new VolumeProductDecorator(product, 5);
        System.out.println(volumeDecorator.getPriceIncludingVAT());
    }
}