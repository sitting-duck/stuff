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
        for(Part part: allParts) {
            if (part.getId() == selectedPart.getId() &&
            part.getName().equals(selectedPart.getName()) &&
            part.getPrice() == selectedPart.getPrice() &&
            part.getStock() == selectedPart.getStock() &&
            part.getMin() == selectedPart.getMin() &&
            part.getMax() == selectedPart.getMax()) {
                if(selectedPart instanceof InHousePart &&
                ((InHousePart) part).getMachineId() == ((InHousePart) selectedPart).getMachineId()) {
                    return allParts.remove(part);
                } else if(selectedPart instanceof OutSourcedPart &&
                    ((OutSourcedPart)part).getCompanyName().equals(((OutSourcedPart) selectedPart).getCompanyName())) {
                    return allParts.remove(part);
                }
            }
        }
        System.out.println("No matching part was found");
        return false;
    }

    public boolean deleteProduct(Product selectedProduct) {
        for(Product product: allProducts) {
            if (product.getId() == selectedProduct.getId() &&
                    product.getName().equals(selectedProduct.getName()) &&
                    product.getPrice() == selectedProduct.getPrice() &&
                    product.getStock() == selectedProduct.getStock() &&
                    product.getMin() == selectedProduct.getMin() &&
                    product.getMax() == selectedProduct.getMax()) {
                return allProducts.remove(product);
            }
        }
        System.out.println("No matching part was found");
        return false;
    }

    public ObservableList<Part> getAllParts() { return allParts; }

    public ObservableList<Product> getAllProducts() {
        System.out.println("getAllProducts(): ");
        for(Product product : allProducts) {
            System.out.println("Product: " + product.getName());
        }
        return allProducts;
    }

    public int newProductId() {
        int newId = 0;
        for (Product product : allProducts) {
            if(newId <= product.getId()) {
                newId = product.getId();
            }
        }
        return ++newId;
    }

    public int newPartId() {
        int newId = 0;
        for (Part part : allParts) {
            if(newId <= part.getId()) {
                newId = part.getId();
            }
        }
        return ++newId;
    }
}
