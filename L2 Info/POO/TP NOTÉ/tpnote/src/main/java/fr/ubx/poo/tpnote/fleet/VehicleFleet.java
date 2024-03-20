package fr.ubx.poo.tpnote.fleet;

import fr.ubx.poo.tpnote.vehicle.*;

public class VehicleFleet {
    private static final int MAX_FLEET_SIZE = 10;
    private Vehicle[] fleet;

    public Boolean addVehicle(Vehicle[] list, Vehicle vehicle) {
        for (int i = 0; i < MAX_FLEET_SIZE; i++) {
            if (fleet[i].getId() == vehicle.getId()) {
                return false;
            }
            if (fleet[i] == null) {
                fleet[i] = vehicle;
                return true;
            }
        }
        return false;
    }

    public Vehicle bestChoiceWithTimeConstraint(VehicleFleet vehicleFleet, double distance, 
                                                double averageSpeed, int numberOfPeople, double maxTime) {
        double MinPrice = 999;
        Vehicle bestVehicle = null;
        for (int i = 1; i < fleet.length; i++) {
            double currentPrice = fleet[i].travelPricePerPerson(distance, averageSpeed, numberOfPeople);
            double travelTime = fleet[i].travelTime(distance, averageSpeed);
            if (currentPrice < MinPrice && travelTime < maxTime) {
                MinPrice = currentPrice;
                bestVehicle = fleet[i];
            }
        }
        return bestVehicle;
    }

}

