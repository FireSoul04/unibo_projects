package it.unibo.shapes.impl;

import java.math.*;
import it.unibo.shapes.api.*;

public class Circle implements Shape {
    
    private final double radius;
    
    public Circle(double radius) {
        this.radius = radius;
    }

    public final double getRadius() {
        return this.radius;
    }

    public final double getPerimeter() {
        return 2 * Math.PI * radius;
    }

    public final double getArea() {
        return Math.PI * radius * radius;
    }
}
