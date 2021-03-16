package inventoryApp;

import inventoryApp.Part;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class Product {

    final ObservableList<InHousePart> inHousePartsList = null;//FXCollections.observableArrayList(brakes, wheel, seat);

    private ObservableList<Part> associatedParts;
    private int id;
    private String name;
    private double price;
    private int stock;
    private int min;
    private int max;

    public Product(int id, String name, double price, int stock, int min, int max) {}

    public void setId(int id) { this.id = id;}

    public void setPrice(double price) { this.price = price; }

    public void setStock(int stock) { this.stock = stock; }

    public void setMin(int min) { this.min = min; }

    public void setMax(int max) { this.max = max; }

    public int getId() { return this.id; }

    public String getName() { return this.name; }

    public double getPrice() { return this.price; }

    public int getStock() { return this.stock; }

    public int getMin() { return this.min; }

    public int getMax() { return this.max; }

    public void addAssociatedPart(Part part) {  }

    public boolean deleteAssociatedPart(Part selectedAssociatedPart) { return true; }

    public ObservableList<Part> getAllAssociatedParts() { return associatedParts; }






}
