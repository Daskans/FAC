package fr.ubx.poo.tpnote.vehicle;

public abstract class Vehicle {
    private final String id;
    private final int maxSeatingPlaces;
    private final double maxEnergyCapacity;
    private double currentEnergy;
    private double energyPrice;
    private double energyConsumption;

    public Vehicle(String id, int maxSeatingPlaces, double maxEnergyCapacity, double currentEnergy, double energyPrice, double energyConsumption) {
        this.id = id;
        this.maxSeatingPlaces = maxSeatingPlaces;
        this.maxEnergyCapacity = maxEnergyCapacity;
        this.currentEnergy = currentEnergy;
        this.energyPrice = energyPrice;
        this.energyConsumption = energyConsumption;
    }

    public String getId() { return id; }
    public int getMaxSeatingPlaces() { return maxSeatingPlaces; }
    public double getMaxEnergyCapacity() { return maxEnergyCapacity; }
    public double getCurrentEnergy() { return currentEnergy; }
    public double getEnergyPrice() { return energyPrice; }
    public double getEnergyConsumption() { return energyConsumption; }

    abstract public String getEnergyUnit();

    abstract public String getEnergyConsumptionUnit();

    abstract public String getEnergyPriceUnit();

    abstract public double chargingTime(double energy);

    abstract public double energyCost(double distance, double avgSpeed);

    public double travelTime(double distance, double avgSpeed) {
        return distance / avgSpeed + 
            (chargingTime(getMaxEnergyCapacity() - getCurrentEnergy()) * 
            ((int)energyCost(distance, avgSpeed) / getMaxEnergyCapacity()));
    }

    public double travelPricePerPerson(double distance, double avgSpeed, int nbPassengers) {
        return energyCost(distance, avgSpeed) / nbPassengers;
    }

}
