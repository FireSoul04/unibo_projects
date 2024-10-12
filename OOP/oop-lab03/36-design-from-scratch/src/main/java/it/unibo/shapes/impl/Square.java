package it.unibo.shapes.impl;

import it.unibo.shapes.api.*;

public class Square implements Polygon {
    
    private final int EDGE_COUNT = 4;

    private final double edge;

    public Square(final double edge) {
        this.edge = edge;
    }

    public final double getPerimeter() {
        return this.EDGE_COUNT * this.edge;
    }

    public final double getArea() {
        return this.edge * this.edge;
    }

    public final int getEdgeCount() {
        return this.EDGE_COUNT;
    }
}