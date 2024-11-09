package it.unibo.design.robot.impl;

import it.unibo.design.robot.api.RobotWithArms;

public class RobotWithTwoArms extends BaseRobot implements RobotWithArms {

    private static final double MOVEMENT_CONSUMPTION_PER_OBJECT = 0.5;

    private final BasicArm rightArm;
    private final BasicArm leftArm;

    public RobotWithTwoArms(String robotName) {
        super(robotName);
        rightArm = new BasicArm("Right arm");
        leftArm = new BasicArm("Left arm");
    }

    @Override
    protected double getBatteryRequirementForMovement() {
        return super.getBatteryRequirementForMovement()
            + MOVEMENT_CONSUMPTION_PER_OBJECT * this.getCarriedItemsCount();
    }

    @Override
    public boolean pickUp() {
        boolean canPickUp = true;

        consumeBattery(BasicArm.getConsumptionForPickUp());

        if (!rightArm.isGrabbing()) {
            rightArm.pickUp();
        } else if (!leftArm.isGrabbing()) {
            leftArm.pickUp();
        } else {
            canPickUp = false;
        }

        return canPickUp;
    }

    @Override
    public boolean dropDown() {
        boolean canDropDown = true;

        consumeBattery(BasicArm.getConsumptionForDropDown());

        if (rightArm.isGrabbing()) {
            rightArm.dropDown();
        } else if (leftArm.isGrabbing()) {
            leftArm.dropDown();
        } else {
            canDropDown = false;
        }

        return canDropDown;
    }

    @Override
    public int getCarriedItemsCount() {
        int carriedItemsCount = 0;
        if (rightArm.isGrabbing()) {
            carriedItemsCount++;
        }
        if (leftArm.isGrabbing()) {
            carriedItemsCount++;
        }
        return carriedItemsCount;
    }
}
