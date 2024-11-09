package it.unibo.shapes.impl;

import it.unibo.shapes.api.*;

public class Triangle implements Polygon {
    
    private final int EDGE_COUNT = 3;

    private final double base;
    private final double height;

    public Triangle (
        final double base,
        final double height
    ) {
        this.base = base;
        this.height = height;
    }

    public final double getPerimeter() {
        return this.EDGE_COUNT * this.base;
    }

    public final double getArea() {
        return this.base * this.height / 2;
    }

    public final int getEdgeCount() {
        return this.EDGE_COUNT;
    }
}