package it.unibo.collections.design;

import it.unibo.collections.design.api.Product;

public class ComparableProduct extends ProductImpl implements Comparable<Product> {

    public ComparableProduct(final String name, final double quantity) {
        super(name, quantity);
    }

    @Override
    public int compareTo(final Product p) {
        return this.getName().compareTo(p.getName());
    }
}
