package it.unibo.design.robot.impl;

import java.util.Arrays;

public abstract class CommandableRobotPart extends RobotPart {

    private final String[] commands;

    public CommandableRobotPart(final String[] commands) {
        super();
        this.commands = commands;
    }

    public String[] availableCommands() {
        return Arrays.copyOf(commands, commands.length);
    }

    public abstract void sendCommand(final String command);
}
