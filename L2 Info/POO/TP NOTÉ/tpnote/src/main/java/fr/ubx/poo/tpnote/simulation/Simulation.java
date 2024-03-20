package fr.ubx.poo.tpnote.simulation;

import fr.ubx.poo.tpnote.fleet.VehicleFleet;
import fr.ubx.poo.tpnote.vehicle.ElectricCar;
import fr.ubx.poo.tpnote.vehicle.ThermicCar;
import fr.ubx.poo.tpnote.vehicle.Vehicle;

public class Simulation {

    public static void main(String[] args) {
        Vehicle electricCar2s = new ElectricCar(
                "1",
                2,
                75,
                37.5,
                0.18,
                15,
                3
        );
        Vehicle electricCar5s = new ElectricCar(
                "2",
                5,
                120,
                60,
                0.18,
                25,
                4
        );
        Vehicle thermicCar = new ThermicCar(
                "3",
                4,
                60,
                30,
                1.78,
                6
        );

        Vehicle thermicBus = new ThermicCar(
                "4",
                8,
                80,
                40,
                1.78,
                10
        );
        // test charging time
        testChargingTime(electricCar5s, 240);
        testChargingTime(thermicCar, 80);

        double distance = 200;
        double averageSpeed = 110;
        // test energy cost
        testEnergyCost(electricCar5s, distance, averageSpeed);
        testEnergyCost(thermicCar, distance, averageSpeed);

        // test travelPricePerPerson
        int numberOfPeople = 3;
        testTravelPricePerPerson(electricCar5s, distance, averageSpeed, numberOfPeople);
        testTravelPricePerPerson(thermicCar, distance, averageSpeed, numberOfPeople);
/*/
        VehicleFleet vehicleFleet = new VehicleFleet();
        if (vehicleFleet.addVehicle(electricCar2s)
            && vehicleFleet.addVehicle(electricCar5s)
            && vehicleFleet.addVehicle(thermicCar)
            && vehicleFleet.addVehicle(thermicBus))
            System.out.println(vehicleFleet);
        else {
            System.out.println("At least one vehicle couldn't be added");
            return;
        }
        // test bestChoiceWithTimeConstraint
        distance = 500;
        averageSpeed = 100;
        numberOfPeople = 3;
        double maxTime = 10;
        testBestChoiceWithTimeConstraint(vehicleFleet, distance, averageSpeed, numberOfPeople, maxTime);
        maxTime = 7;
        testBestChoiceWithTimeConstraint(vehicleFleet, distance, averageSpeed, numberOfPeople, maxTime);*/

        //vehicleFleet.test(distance, averageSpeed, numberOfPeople);
    }
    private static void testChargingTime(Vehicle vehicle, double energyNeeded) {
        System.out.println("Vehicle " + vehicle.getId() + " :\n\tcharging time from "  +
                vehicle.getCurrentEnergy() + vehicle.getEnergyUnit() + " to " +
                energyNeeded + vehicle.getEnergyUnit() + "=\t" +
                vehicle.chargingTime(energyNeeded) + "h");
    }
    private static void testEnergyCost(Vehicle vehicle, double distance, double averageSpeed) {
        System.out.println("Vehicle " + vehicle.getId() +
                " :\n\tenergy cost of a travel of " + distance + "km" +
                " at the speed of " +  averageSpeed + "km/h=\t" +
                vehicle.energyCost(distance, averageSpeed) + vehicle.getEnergyUnit());
    }

    private static void testTravelPricePerPerson(Vehicle vehicle, double distance, double averageSpeed,
                                                 int numberOfPeople) {
        System.out.println("Vehicle " + vehicle.getId() +
                ":\n\tprice per person for a travel of  " + distance + "km" +
                " at the speed of " +  averageSpeed + "km/h" +
                " with "+ numberOfPeople + " people=\t" +
                vehicle.travelPricePerPerson(distance, averageSpeed, numberOfPeople) + "euros");
    }/*
    private static void testBestChoiceWithTimeConstraint(VehicleFleet vehicleFleet, double distance, double averageSpeed,
                                                         int numberOfPeople, double maxTime) {
        Vehicle vehicle = vehicleFleet.bestChoiceWithTimeConstraint(distance, averageSpeed, numberOfPeople, maxTime);
        if (vehicle != null)
            System.out.println("Vehicle " + vehicle.getId() +
                    ":\n\tbest price per person for a travel of  " + distance + "km" +
                    " at the speed of " +  averageSpeed + "km/h" +
                    " with "+ numberOfPeople + " people and a travel time less than " + maxTime + "h\n" +
                    "\ttravel price per person  =" + vehicle.travelPricePerPerson(distance, averageSpeed, numberOfPeople) + "euros\n" +
                    "\ttravel time =" + vehicle.travelTime(distance, averageSpeed) + "h");

    }*/
}

