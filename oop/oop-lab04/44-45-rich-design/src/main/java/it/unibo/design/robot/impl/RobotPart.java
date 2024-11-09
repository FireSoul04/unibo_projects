package it.unibo.design.robot.impl;

public abstract class RobotPart {

    private static int idCounter = 0;
    private int id;
    private boolean isPoweredOn;

    public RobotPart() {
        this.id = idCounter;
        this.isPoweredOn = false;
        idCounter++;
    }
    
    public void turnOn() {
        isPoweredOn = true;
    }

    public void turnOff() {
        isPoweredOn = false;
    }

    public boolean isActive() {
        return isPoweredOn;
    }

    public int getID() {
        return id;
    }

    @Override
    public boolean equals(final Object o) {
        if (o instanceof RobotPart) {
            final RobotPart other = (RobotPart)o;
            return this.id == other.getID();
        }
        return false;
    }

    public abstract double getBatteryConsumption();
}
