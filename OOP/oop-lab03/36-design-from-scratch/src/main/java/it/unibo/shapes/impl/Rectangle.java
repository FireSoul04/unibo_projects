package it.unibo.shapes.impl;

import it.unibo.shapes.api.*;

public class Rectangle implements Polygon {
    
    private final int EDGE_COUNT = 4;

    private final double base;
    private final double height;

    public Rectangle (
        final double base,
        final double height 
    ) {
        this.base = base;
        this.height = height;
    }

    public final double getPerimeter() {
        return this.base * 2 + this.height * 2;
    }

    public final double getArea() {
        return this.base * this.height;
    }

    public final int getEdgeCount() {
        return this.EDGE_COUNT;
    }
}