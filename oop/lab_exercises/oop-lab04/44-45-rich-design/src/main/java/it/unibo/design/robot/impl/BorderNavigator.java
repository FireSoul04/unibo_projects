package it.unibo.design.robot.impl;

import java.util.Random;

import it.unibo.design.robot.environment.api.Position2D;
import it.unibo.design.robot.environment.impl.RobotPosition;

public class BorderNavigator extends RobotPart {
    
    private static double BATTERY_CONSUMPTION = 0.2;

    private Position2D facingDirection;

    public BorderNavigator() {
        super();
        facingDirection = getRandomDirection();
    }

    public double getBatteryConsumption() {
        return BATTERY_CONSUMPTION;
    }

    public Position2D getFacingDirecton() {
        return facingDirection;
    }

    public void rotate() {
        facingDirection = new RobotPosition(facingDirection.getY(), -facingDirection.getX());
    }

    private Position2D getRandomDirection() {
        final Random r = new Random();
        final int x = r.nextInt(0, 1) * 2 - 1;
        int y = 0;
        if (x == 0) {
            y = r.nextInt(0, 1) * 2 - 1;
        }

        return new RobotPosition(x, y);
    }
}
