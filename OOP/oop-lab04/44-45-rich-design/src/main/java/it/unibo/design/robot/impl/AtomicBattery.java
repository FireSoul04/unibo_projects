package it.unibo.design.robot.impl;

public class AtomicBattery extends RobotPart {
    
    private final double BATTERY_RECHARGE = -50.0;
    private final double BATTERY_TRANSFER_CONSUMPTION = 20.0;
    private double batteryLevel;

    public AtomicBattery() {
        super();
        batteryLevel = 100.0;
    }

    public double getBatteryConsumption() {
        batteryLevel = batteryLevel - BATTERY_TRANSFER_CONSUMPTION;
        return BATTERY_RECHARGE;
    }
}
