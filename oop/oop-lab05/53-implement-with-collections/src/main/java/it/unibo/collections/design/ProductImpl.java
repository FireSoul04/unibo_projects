package it.unibo.collections.design;

import it.unibo.collections.design.api.Product;

public class ProductImpl implements Product {

    private final String name;
    private double quantity;

    public ProductImpl(final String name, final double quantity) {
        this.name = name;
        this.quantity = quantity;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getQuantity() {
        return quantity;
    }

    public boolean equals(final Object o) {
        return this == o || (o instanceof Product && this.name == ((Product)o).getName());
    }

    public String toString() {
        return "Product [" +
            "name: " + this.name + ", " + 
            "quantity: " + this.quantity + 
            "]";
    }
}
