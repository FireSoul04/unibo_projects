package it.unibo.design.robot.impl;

public class BasicArm {

    private static double CONSUMPTION_PICK_UP = 0.5;
    private static double CONSUMPTION_DROP_DOWN = 0.2;

    private boolean isBusy;

    private String armName;

    public BasicArm(final String armName) {
        this.armName = armName;
        isBusy = false;
    }

    public boolean isGrabbing() {
        return isBusy;
    }
    
    public void pickUp() {
        if (!isBusy) {
            isBusy = true;
        }
    }

    public void dropDown() {
        if (isBusy) {
            isBusy = false;
        }
    }

    public static double getConsumptionForPickUp() {
        return BasicArm.CONSUMPTION_PICK_UP;
    }

    public static double getConsumptionForDropDown() {
        return BasicArm.CONSUMPTION_DROP_DOWN;
    }
}