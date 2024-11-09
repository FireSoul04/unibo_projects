package it.unibo.design.robot.impl;

public class RobotArm extends CommandableRobotPart {
    
    private double BATTERY_CONSUMPTION_CARRYING = 0.2;

    private boolean isBusy;

    public RobotArm() {
        super(new String[] {
            "pick",
            "drop"   
        });
        isBusy = false;
    }

    public boolean isGrabbing() {
        return isBusy;
    }
    
    @Override
    public void sendCommand(final String command) {
        if (isActive()) {
            if (command.equals("pick")) {
                pickUp();
            } else if (command.equals("drop")) {
                dropDown();
            } else {
                System.out.println("Command not recognized");
            }
        } else {
            System.out.println("Arm is not active");
        }
    }
    
    private void pickUp() {
        if (!isBusy) {
            isBusy = true;
        } else {
            System.out.println("Cannot pick up, arm is carrying too many objects");
        }
    }

    private void dropDown() {
        if (isBusy) {
            isBusy = false;
        } else {
            System.out.println("Cannot drop down, arm is not carrying any object");
        }
    }

    public double getBatteryConsumption() {
        if (isBusy) {
            return BATTERY_CONSUMPTION_CARRYING;
        }
        return 0.0;
    }
}
