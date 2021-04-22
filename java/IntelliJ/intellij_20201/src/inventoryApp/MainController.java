package inventoryApp;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class MainController implements Initializable {

    public Label TheLabel;
    public StackPane anchorPane;
    public GridPane gridPaneRoot;
    public GridPane gridPaneTwoColumns;
    public VBox leftVBox;
    public HBox partsSearchRow;
    public Label partsLabel;

    public TextField partsSearchField;

    public HBox partTableHBox;
    public TableView partTable;
    public HBox partButtonHBox;
    public Button addPartBtn;
    public Button modifyPartBtn;
    public Button deletePartBtn;
    public VBox rightVBox;
    public HBox productSearchRow;
    public Label productsLabel;
    public TextField productsSearchField;
    public HBox productTableHBox;
    public TableView productTable;
    public HBox productButtonHBox;
    public Button addProductBtn;
    public Button modifyProductBtn;
    public Button deleteProductBtn;

    private static Inventory inventory = new Inventory();

    public void initPartTable() throws IOException {
        System.out.println("initPartTable()");

        this.partTable.setEditable(true);

        TableColumn partIDCol = new TableColumn("Part ID");
        partIDCol.setCellValueFactory(new PropertyValueFactory<>("id"));

        TableColumn partNameCol = new TableColumn("Part Name");
        partNameCol.setCellValueFactory(new PropertyValueFactory<>("name"));

        TableColumn inventoryLevelCol = new TableColumn("Inventory Level");
        inventoryLevelCol.setCellValueFactory(new PropertyValueFactory<>("stock"));

        TableColumn priceCostPerUnitCol = new TableColumn("Price/Cost per Unit");
        priceCostPerUnitCol.setCellValueFactory(new PropertyValueFactory<>("price"));

        partTable.getColumns().addAll(partIDCol, partNameCol, inventoryLevelCol, priceCostPerUnitCol);

        partTable.setItems(inventory.getAllParts());
    }

    public void initProductTable() throws IOException {
        System.out.println("initProductTable()");
        this.productTable.setEditable(true);

        TableColumn productIDCol = new TableColumn("Part ID");
        productIDCol.setCellValueFactory(new PropertyValueFactory<>("id"));

        TableColumn productNameCol = new TableColumn("Part Name");
        productNameCol.setCellValueFactory(new PropertyValueFactory<>("name"));

        TableColumn inventoryLevelCol = new TableColumn("Inventory Level");
        inventoryLevelCol.setCellValueFactory(new PropertyValueFactory<>("stock"));

        TableColumn priceCostPerUnitCol = new TableColumn("Price/Cost per Unit");
        priceCostPerUnitCol.setCellValueFactory(new PropertyValueFactory<>("price"));

        productTable.getColumns().addAll(productIDCol, productNameCol, inventoryLevelCol, priceCostPerUnitCol);

        productTable.setItems(inventory.getAllProducts());
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        try {
            initPartTable();
        } catch(Exception e) {
            System.out.println("Error initializing parts table: " + e.toString());
        }
        try {
            initProductTable();
        } catch(Exception e) {
            System.out.println("Error initializing products table");
        }
        System.out.println("Initialized");
    }

    public void toAddPartForm(ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("AddPartForm.fxml"));
        Stage stage = (Stage)((Node)actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root, 600, 400);
        stage.setTitle("Add Part");
        stage.setScene(scene);
        stage.show();
    }

    public void toAddProductForm(ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("AddProductForm.fxml"));
        Stage stage = (Stage)((Node)actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root, 600, 400);
        stage.setTitle("Add Part");
        stage.setScene(scene);
        stage.show();
    }

    public void toModifyPartForm(ActionEvent actionEvent) throws IOException {
        Part part = (Part)partTable.getSelectionModel().getSelectedItem();

        if(part == null) {
            System.out.println("Error: no part selected");
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("No part selected");
            alert.setHeaderText("No part selected");
            alert.setContentText("No part selected. Please select a part to modify.");
            alert.showAndWait();
        } else {
            ModifyPartController.setPart(part);
            Parent root = FXMLLoader.load(getClass().getResource("ModifyPartForm.fxml"));
            Stage stage = (Stage)((Node)actionEvent.getSource()).getScene().getWindow();
            Scene scene = new Scene(root, 600, 400);
            stage.setTitle("Modify Part");
            stage.setScene(scene);
            stage.show();
        }
    }

    public void toModifyProductForm(ActionEvent actionEvent) throws IOException {
        Product product = (Product)productTable.getSelectionModel().getSelectedItem();

        if(product == null) {
            System.out.println("Error: no product selected");
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("No product selected");
            alert.setHeaderText("No product selected");
            alert.setContentText("No product selected. Please select a product to modify.");
            alert.showAndWait();
        } else {
            ModifyProductController.setProduct(product);
            Parent root = FXMLLoader.load(getClass().getResource("ModifyProductForm.fxml"));
            Stage stage = (Stage)((Node)actionEvent.getSource()).getScene().getWindow();
            Scene scene = new Scene(root, 600, 400);
            stage.setTitle("Modify Product");
            stage.setScene(scene);
            stage.show();
        }
    }

    public void OnDeletePartBtnClicked(ActionEvent actionEvent) {
        System.out.println("OnDeletePartBtnClicked: ");
        Part part = (Part)partTable.getSelectionModel().getSelectedItem();

        if(part == null) {
            System.out.println("No part selected.");
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("No part selected");
            alert.setHeaderText("No part selected");
            alert.setContentText("No part selected. Please select a part to delete.");
            alert.showAndWait();
            return;
        } else {
            System.out.println("part: " + part.getName() + " selected.");
            inventory.deletePart(part);
            partTable.setItems(inventory.getAllParts());
        }
    }

    public void OnDeleteProductBtnClicked(ActionEvent actionEvent) {
        System.out.println("OnDeleteProductBtnClicked: ");
        Product product = (Product)productTable.getSelectionModel().getSelectedItem();

        if(product == null) {
            System.out.println("No product selected.");
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("No product selected");
            alert.setHeaderText("No product selected");
            alert.setContentText("No product selected. Please select a product to delete.");
            alert.showAndWait();
            return;
        } else {
            System.out.println("product: " + product.getName() + " selected.");
            inventory.deleteProduct(product);
            productTable.setItems(inventory.getAllProducts());
        }
    }

    public void getPartSearchResultsHandler(ActionEvent actionEvent) {
        String queryText = this.partsSearchField.getText();
        System.out.println("getPartSearchResultsHandler: " + queryText);

        if(queryText.isEmpty()) {
            this.partTable.setItems(inventory.getAllParts());
        }

        ObservableList<Part> parts = inventory.lookupPart(queryText);

        if(parts.size() == 0) {
            try {
                int idNum = Integer.parseInt(queryText);
                Part part = inventory.lookupPart(idNum);
                parts.add(part);
                this.partTable.setItems(parts);
                this.partsSearchField.setText("");
            } catch(NumberFormatException exception) {
                // string is not a number so we search by part name instead of ID
                System.out.println("Error: " + queryText + " cannot be converted to Integer.");
//                Alert alert = new Alert(Alert.AlertType.WARNING);
//                alert.setTitle("Error: " + queryText + " cannot be converted to Integer.");
//                alert.setHeaderText("Error: " + queryText + " cannot be converted to Integer.");
//                alert.setContentText("Error: " + queryText + " cannot be converted to Integer.");
//                alert.showAndWait();
            }
        }
        this.partTable.setItems(parts);
    }

    public void getProductSearchResultsHandler(ActionEvent actionEvent) {
        String queryText = this.productsSearchField.getText();
        System.out.println("getProductSearchResultsHandler: " + queryText);

        if(queryText.isEmpty()) {
            this.productTable.setItems(inventory.getAllProducts());
        }

        ObservableList<Product> products = inventory.lookupProduct(queryText);

        if(products.size() == 0) {
            try {
                int idNum = Integer.parseInt(queryText);
                Product product = inventory.lookupProduct(idNum);
                products.add(product);
                this.productTable.setItems(products);
                this.productsSearchField.setText("");
            } catch(NumberFormatException exception) {
                // string is not a number so we search by part name instead of ID
                System.out.println("Error: " + queryText + " cannot be converted to Integer.");
//                Alert alert = new Alert(Alert.AlertType.WARNING);
//                alert.setTitle("Error: " + queryText + " cannot be converted to Integer.");
//                alert.setHeaderText("Error: " + queryText + " cannot be converted to Integer.");
//                alert.setContentText("Error: " + queryText + " cannot be converted to Integer.");
//                alert.showAndWait();
            }
        }
        this.productTable.setItems(products);
    }

    public void onExitBtnClicked(ActionEvent actionEvent) {
        Platform.exit();
        System.exit(0);
    }
}
