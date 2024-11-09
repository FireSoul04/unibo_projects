package it.unibo.design.robot.impl;

import it.unibo.design.robot.api.ComposableRobot;
import it.unibo.design.robot.environment.api.Position2D;
import it.unibo.design.robot.environment.impl.RobotEnvironment;

public class SimpleComposableRobot extends BaseRobot implements ComposableRobot {
   
    private static final int MAX_ATTACHABLE_PART = 4;
    private final RobotPart[] attachedParts;
    private int partsTail;

    public SimpleComposableRobot(final String robotName) {
        super(robotName);
        attachedParts = new RobotPart[MAX_ATTACHABLE_PART];
        partsTail = 0;
    }

    public void attachComponent(final RobotPart part) {
        if (partsTail < MAX_ATTACHABLE_PART) {
            attachedParts[partsTail] = part;
            partsTail++;
        } else {
            System.out.println("Max number of attachable parts reached: " + MAX_ATTACHABLE_PART);    
        }
    }

    public void detachComponent(final RobotPart part) {
        final int index = getIndexOfPartAttached(part);

        if (index >= 0) {
            for (int i = partsTail - 1; i >= partsTail; i--) {
                attachedParts[i] = attachedParts[i + 1];
            }
            partsTail--;
        } else {
            System.out.println("Part " + part + " is not attached to " + this.toString());
        }
    }

    private int getIndexOfPartAttached(final RobotPart part) {
        for (int i = 0; i <= partsTail; i++) {
            if (attachedParts[i].equals(part)) {
                return i; 
            }
        }
        return -1; // The part passed in input is not attached at this robot
    }

    public void doCycle() {
        for (final RobotPart part : attachedParts) {
            if (part.isActive()) {
                this.consumeBattery(part.getBatteryConsumption());
            }
            if (part instanceof BorderNavigator) {
                final BorderNavigator navi = (BorderNavigator)part;
                final Position2D facingPosition = navi.getFacingDirecton();

                move(facingPosition.getX(), facingPosition.getY());

                if (isOnBorder()) {
                    navi.rotate();
                }
            }
        }
    }

    private boolean isOnBorder() {
        return
            this.getPosition().getX() == RobotEnvironment.X_LOWER_LIMIT ||
            this.getPosition().getX() == RobotEnvironment.X_UPPER_LIMIT ||
            this.getPosition().getY() == RobotEnvironment.Y_LOWER_LIMIT ||
            this.getPosition().getY() == RobotEnvironment.Y_UPPER_LIMIT;
    }
}
