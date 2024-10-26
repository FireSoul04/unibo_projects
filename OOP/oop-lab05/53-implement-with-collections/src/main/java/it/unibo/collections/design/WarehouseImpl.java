package it.unibo.collections.design;

import it.unibo.collections.design.api.Product;
import it.unibo.collections.design.api.Warehouse;

import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class WarehouseImpl implements Warehouse{

    private final Set<Product> products;
    
    public WarehouseImpl() {
        products = new LinkedHashSet<>();
    }

    @Override
    public void addProduct(final Product p) {
        products.add(p);
    }

    @Override
    public Set<String> allNames() {
        final Set<String> productNames = new HashSet<>();

        for (final Product p : products) {
            productNames.add(p.getName());
        }
        return productNames;
    }

    @Override
    public Set<Product> allProducts() {
        return new LinkedHashSet<>(Set.copyOf(products));
    }

    @Override
    public boolean containsProduct(final Product p) {
        return products.contains(p);
    }

    @Override
    public double getQuantity(final String name) {
        double quantity = 0.0;

        for (final Product p : products) {
            if (name.equals(p.getName())) {
                quantity = p.getQuantity();
            }
        }
        return quantity;
    }
}
