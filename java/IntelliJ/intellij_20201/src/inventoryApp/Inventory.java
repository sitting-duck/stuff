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
        allProducts.add(newProduct);
    }

    public Part lookupPart(int partId) {
        return (Part)null;
    }

    public Product lookupProduct(int productId) {
        return (Product)null;
    }

    public ObservableList<Part> lookupPart(String partName) {
        return (ObservableList<Part>)null;
    }

    public ObservableList<Product> lookupProduct(String productName) {
        return (ObservableList<Product>)null;
    }

    public void updatePart(int index, Part selectedPart) {}

    public void updateProduct(int index, Product newProduct) {}

    public boolean deletePart(Part selectedPart) {
        return true;
    }

    public boolean deleteProduct(Product selectedProduct) {
        return true;
    }

    public ObservableList<Part> getAllParts() { return (ObservableList<Part>)null; }

    public ObservableList<Product> getAllProducts() { return (ObservableList<Product>)null; }
}
