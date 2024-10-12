package it.unibo.shapes.test;

import it.unibo.shapes.api.*;
import it.unibo.shapes.impl.*;

public class WorkWithShapes {
    public static void main(String[] args) {

        final Shape circle = new Circle(1);
        final Shape square = new Square(4.0);
        final Shape rect = new Rectangle(3.0, 2.5);
        final Shape tri = new Triangle(5.0, 2.5);

        System.out.println("Circle: perimeter=" + circle.getPerimeter() + " area=" + circle.getArea());
        System.out.println("Square: perimeter=" + square.getPerimeter() + " area=" + square.getArea());
        System.out.println("Rectangle: perimeter=" + rect.getPerimeter() + " area=" + rect.getArea());
        System.out.println("Triangle: perimeter=" + tri.getPerimeter() + " area=" + tri.getArea());
    }
}
