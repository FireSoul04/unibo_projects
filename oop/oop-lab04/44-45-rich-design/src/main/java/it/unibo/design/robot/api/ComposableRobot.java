package it.unibo.design.robot.api;

import it.unibo.design.robot.impl.RobotPart;

public interface ComposableRobot extends Robot {

    public void attachComponent(final RobotPart part);

    public void detachComponent(final RobotPart part);

    public void doCycle();
}
