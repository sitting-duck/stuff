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
            System.out.println(part.getName());
            System.out.println("\tidMatch: " + (part.getId() == selectedPart.getId()));
            System.out.println("\tnameMatch: " + (part.getName().equals(selectedPart.getName())));
            System.out.println("\tpriceMatch: " + (part.getPrice() == selectedPart.getPrice()));
            System.out.println("\tstockMatch: " + (part.getStock() == selectedPart.getStock()));
            System.out.println("\tminMatch: " + (part.getMin() == selectedPart.getMin()));
            System.out.println("\tmaxMatch: " + (part.getMax() == selectedPart.getMax()));
            System.out.println("\tpart.getMax: " + part.getMax());
            System.out.println("\tselectedPart.getMax: " + selectedPart.getMax());
            if(selectedPart instanceof InHousePart &&
                    ((InHousePart) part).getMachineId() == ((InHousePart) selectedPart).getMachineId()) {
                System.out.println("\tmachineIdMatch: " + (((InHousePart) part).getMachineId() == ((InHousePart) selectedPart).getMachineId()));
            } else if(selectedPart instanceof OutSourcedPart &&
                    ((OutSourcedPart)part).getCompanyName() == ((OutSourcedPart) selectedPart).getCompanyName()) {
                System.out.println("\tcompanyNameMatch: " + (((OutSourcedPart)part).getCompanyName().equals(((OutSourcedPart) selectedPart).getCompanyName())));
            }

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
