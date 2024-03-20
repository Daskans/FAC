package fr.ubx.poo.tpnote.vehicle;

public class ThermicCar extends  Vehicle {
    public ThermicCar(String id, int maxSeatingPlaces, double maxEnergyCapacity, double currentEnergy, double energyPrice, double energyConsumption) {
        super(id, maxSeatingPlaces, maxEnergyCapacity, currentEnergy, energyPrice, energyConsumption);
    }

    public String getEnergyUnit() { return "l"; }

    public String getEnergyConsumptionUnit() { return "l/100km"; }

    public String getEnergyPriceUnit() { return "€/l"; }

    public double chargingTime(double energy) { return 0; }

    public double energyCost(double distance, double avgSpeed) {
        return distance * getEnergyConsumption() / 100 * Math.sqrt(avgSpeed/90);
    }

}

