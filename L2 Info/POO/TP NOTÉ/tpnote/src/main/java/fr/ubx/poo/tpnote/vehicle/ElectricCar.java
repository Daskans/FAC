package fr.ubx.poo.tpnote.vehicle;

public class ElectricCar extends Vehicle{
    private double maxChargingTime;

    public ElectricCar(String id, int maxSeatingPlaces, double maxEnergyCapacity, double currentEnergy, double energyPrice, double energyConsumption, double maxChargingTime) {
        super(id, maxSeatingPlaces, maxEnergyCapacity, currentEnergy, energyPrice, energyConsumption);
        this.maxChargingTime = maxChargingTime;
    }

    public double getMaxChargingTime() {return maxChargingTime; }

    public String getEnergyUnit() { return "Kwh"; }

    public String getEnergyConsumptionUnit() { return "Kwh"; }

    public String getEnergyPriceUnit() { return "€/Kwh"; }

    public double chargingTime(double energy) {
        return (getMaxChargingTime() * energy) / getMaxEnergyCapacity();
    }

    public double energyCost(double distance, double avgSpeed) {
        return distance / avgSpeed * getEnergyConsumption() * Math.sqrt(avgSpeed/90);
    }

}
