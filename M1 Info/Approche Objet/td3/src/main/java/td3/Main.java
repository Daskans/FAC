package td3;

import java.util.Calendar;

import td3.Decorators.*;

public class Main {
    public static void main(String[] args) {
        CostumerProduct milk = new CostumerProduct("milk", 0, 0);
        Calendar expirationDate = Calendar.getInstance();
        expirationDate.set(2026, 0, 1);
        ExpirationDateProductDecorator milkWithDeadline = new ExpirationDateProductDecorator(milk, expirationDate);
        VolumeProductDecorator milkBottle = new VolumeProductDecorator(milkWithDeadline, 0.5);
        PackageProductDecorator milkPackage = new PackageProductDecorator(milkBottle, 12);
        PackageProductDecorator milkPackageCardboard = new PackageProductDecorator(milkPackage, 10);
        System.out.println(milkPackageCardboard.toString());
    }
}