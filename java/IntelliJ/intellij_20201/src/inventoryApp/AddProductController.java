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
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class AddProductController implements Initializable {
    public TextField idTextField;
    public TextField nameTextField;
    public TextField invTextField;
    public TextField priceTextField;
    public TextField minTextField;
    public TextField maxTextField;

    public TextField searchField;
    public Button addButton;
    public Button removePartBtn;
    public Button saveBtn;
    public Button cancelBtn;
    public TableView allPartsTable;
    public TableView productPartsTable;

    private static Inventory inventory = new Inventory();
    private ObservableList<Part> associatedParts = FXCollections.observableArrayList();

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        idTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    idTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });
        nameTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    nameTextField.setText(newValue.replaceAll("[^\\d]", ""));
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
                    priceTextField.setText(newValue.replaceAll("[^\\d]", ""));
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
        productPartsTable.setItems(associatedParts);
    }

    public void saveProduct(ActionEvent actionEvent) throws IOException {

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
            System.out.println("Associated parts list length: " + Integer.toString(associatedParts.size()));
            productPartsTable.setEditable(true);

            productPartsTable.refresh();
            productPartsTable.setVisible(false);
            productPartsTable.setItems(associatedParts);
            productPartsTable.setVisible(true);

        }
    }
}
