package inventoryApp;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class Inventory {

    private static ObservableList<Part> allParts = FXCollections.observableArrayList();

    private static ObservableList<Product> allProducts = FXCollections.observableArrayList();

    public void addPart(Part newPart) {
        allParts.add(newPart);
    }

    public void addProduct(Product newProduct) {
        System.out.println("addProduct(): " + newProduct.getName());
        allProducts.add(newProduct);
    }

    public Part lookupPart(int partId) {
        for( Part part : allParts ) {
            if(part.getId() == partId) {
                return part;
            }
        }
        return null;
    }

    public Product lookupProduct(int productId) {
        for( Product product : allProducts ) {
            if(product.getId() == productId) {
                return product;
            }
        }
        return null;
    }

    public ObservableList<Part> lookupPart(String partName) {
        ObservableList<Part> namedParts = FXCollections.observableArrayList();
        for ( Part part : allParts ) {
            if(part.getName().toLowerCase().contains(partName.toLowerCase())) {
                namedParts.add(part);
            }
        }
        return namedParts;
    }

    public ObservableList<Product> lookupProduct(String productName) {
        ObservableList<Product> namedProducts = FXCollections.observableArrayList();
        for ( Product product : allProducts ) {
            if(product.getName().toLowerCase().contains(productName.toLowerCase())) {
                namedProducts.add(product);
            }
        }
        return namedProducts;
    }

    public void updatePart(int index, Part selectedPart) {}

    public void updateProduct(int index, Product newProduct) {}

    public boolean deletePart(Part selectedPart) {
        // TODO: finish writing delete part
        for(Part part: allParts) {
            if (part.getId() == selectedPart.getId() &&
            part.getNaM) {

            }
        }
        return allParts.remove(selectedPart);
    }

    public boolean deleteProduct(Product selectedProduct) { return allProducts.remove(selectedProduct); }

    public ObservableList<Part> getAllParts() { return allParts; }

    public ObservableList<Product> getAllProducts() {
        System.out.println("getAllProducts(): ");
        for(Product product : allProducts) {
            System.out.println("Product: " + product.getName());
        }
        return allProducts;
    }
}
