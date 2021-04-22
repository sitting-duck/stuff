package inventoryApp;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.nio.charset.CodingErrorAction;
import java.util.ResourceBundle;

public class ModifyProductController implements Initializable {

    public static Product product;
    public static Product productOriginal;

    public TextField searchField;
    public Button addButton;
    public Button removePartBtn;
    public Button saveBtn;
    public Button cancelBtn;
    public TextField idTextField;
    public TextField nameTextField;
    public TextField invTextField;
    public TextField priceTextField;
    public TextField minTextField;
    public TextField maxTextField;

    public TableView allPartsTable;
    public TableView productPartsTable;
    private ObservableList<Part> associatedParts = FXCollections.observableArrayList();
    private static Inventory inventory = new Inventory();

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        productOriginal = new Product(product.getId(), product.getName(), product.getPrice(), product.getStock(), product.getMin(), product.getMax());

        idTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    idTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });
        invTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    invTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });
        priceTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    priceTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });
        minTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    minTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });
        maxTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    maxTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });

        idTextField.setText(Integer.toString(product.getId()));
        idTextField.setEditable(false);
        idTextField.setDisable(true);
        nameTextField.setText(product.getName());
        priceTextField.setText(Double.toString(product.getPrice()));
        maxTextField.setText(Integer.toString(product.getMax()));
        minTextField.setText(Integer.toString(product.getMin()));
        invTextField.setText(Integer.toString(product.getStock()));

        if(product.getAllAssociatedParts() != null) {
            System.out.println("associated part list size: " + Integer.toString(product.getAllAssociatedParts().size()));
            for(Part part : product.getAllAssociatedParts()) {
                associatedParts.add(part);
            }
        }

        this.allPartsTable.setEditable(true);
        this.productPartsTable.setEditable(true);

        TableColumn productIDCol = new TableColumn("Part ID");
        productIDCol.setCellValueFactory(new PropertyValueFactory<>("id"));

        TableColumn productNameCol = new TableColumn("Part Name");
        productNameCol.setCellValueFactory(new PropertyValueFactory<>("name"));

        TableColumn inventoryLevelCol = new TableColumn("Inventory Level");
        inventoryLevelCol.setCellValueFactory(new PropertyValueFactory<>("stock"));

        TableColumn priceCostPerUnitCol = new TableColumn("Price/Cost per Unit");
        priceCostPerUnitCol.setCellValueFactory(new PropertyValueFactory<>("price"));

        allPartsTable.getColumns().addAll(productIDCol, productNameCol, inventoryLevelCol, priceCostPerUnitCol);


        allPartsTable.setItems(inventory.getAllParts());
        System.out.println("Set Part Table 1 parts list length: " + Integer.toString(inventory.getAllParts().size()));

        TableColumn productIDCol2 = new TableColumn("Part ID");
        productIDCol2.setCellValueFactory(new PropertyValueFactory<>("id"));

        TableColumn productNameCol2 = new TableColumn("Part Name");
        productNameCol2.setCellValueFactory(new PropertyValueFactory<>("name"));

        TableColumn inventoryLevelCol2 = new TableColumn("Inventory Level");
        inventoryLevelCol2.setCellValueFactory(new PropertyValueFactory<>("stock"));

        TableColumn priceCostPerUnitCol2 = new TableColumn("Price/Cost per Unit");
        priceCostPerUnitCol2.setCellValueFactory(new PropertyValueFactory<>("price"));
        productPartsTable.getColumns().addAll(productIDCol2, productNameCol2, inventoryLevelCol2, priceCostPerUnitCol2);

        System.out.println("Setting bottom table to have " + associatedParts.size() + " parts.");
        productPartsTable.setItems(associatedParts);

    }

    public static void setProduct(Product _product) {
        System.out.println("SetProduct: " + _product.getName());
        product = _product;
    }

    public void saveProduct(ActionEvent actionEvent) throws IOException {
        String newName = nameTextField.getText();

        Double newPrice;
        try {
            newPrice = Double.parseDouble(priceTextField.getText());
        } catch (NumberFormatException e) {
            System.out.println("Error parsing Price to Integer: " + priceTextField.getText());
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Invalid Price");
            alert.setHeaderText("Invalid Price");
            alert.setContentText("Invalid Price");
            alert.showAndWait();
            return;
        }

        Integer newMin;
        try {
            newMin = Integer.parseInt(minTextField.getText());
        } catch (NumberFormatException e) {
            System.out.println("Error parsing Min to Integer: " + minTextField.getText());
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Invalid Min");
            alert.setHeaderText("Invalid Min");
            alert.setContentText("Invalid Min");
            alert.showAndWait();
            return;
        }

        Integer newMax;
        try {
            newMax = Integer.parseInt(maxTextField.getText());
        } catch (NumberFormatException e) {
            System.out.println("Error parsing Max to Integer: " + maxTextField.getText());
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Invalid Max");
            alert.setHeaderText("Invalid Max");
            alert.setContentText("Invalid Max");
            alert.showAndWait();
            return;
        }

        Integer newStock;
        try {
            newStock = Integer.parseInt(invTextField.getText());
        } catch (NumberFormatException e) {
            System.out.println("Error parsing Inventory/Stock to Integer: " + invTextField.getText());
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Invalid Inv");
            alert.setHeaderText("Invalid Inv");
            alert.setContentText("Invalid Inv");
            alert.showAndWait();
            return;
        }

        inventory.deleteProduct(productOriginal);
        product.setName(newName);
        product.setPrice(newPrice);
        product.setMin(newMin);
        product.setMax(newMax);
        product.setStock(newStock);
        inventory.addProduct(product);

        toMainForm(actionEvent);
    }

    public void toMainForm(ActionEvent actionEvent) throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("MainForm.fxml"));
        Stage stage = (Stage) ((Button)actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root, 600, 400);
        stage.setTitle("MainForm");
        stage.setScene(scene);
        stage.show();
    }

    public void addToProductPartsTable(ActionEvent actionEvent) {
        Part part = (Part) allPartsTable.getSelectionModel().getSelectedItem();
        if(part == null) {
            System.out.println("Error: no part selected");
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("No part selected");
            alert.setHeaderText("No part selected");
            alert.setContentText("No part selected. Please select a part to add to product.");
            alert.showAndWait();
        } else {
            associatedParts.add(part);
            product.addAssociatedPart(part);
            System.out.println("Associated parts list length: " + Integer.toString(associatedParts.size()));
            productPartsTable.setEditable(true);
            productPartsTable.setItems(associatedParts);
        }
    }

    public void onRemovePartBtn(ActionEvent actionEvent) {
        Part part = (Part) productPartsTable.getSelectionModel().getSelectedItem();
        int index = productPartsTable.getSelectionModel().getSelectedIndex();
        if(part == null) {
            System.out.println("Error: no part selected");
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("No part selected");
            alert.setHeaderText("No part selected");
            alert.setContentText("No part selected. Please select a part to add to product.");
            alert.showAndWait();
        } else {
            associatedParts.remove(index);
            product.deleteAssociatedPart(part);
            productPartsTable.setItems(associatedParts);
        }
    }
}
