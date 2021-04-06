package inventoryApp;

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

    public static boolean partTableInitialized = false;

    private ObservableList<Part> parts = FXCollections.observableArrayList();
    private ObservableList<Part> products = FXCollections.observableArrayList();

    @FXML
    public void initPartTable() throws IOException {
        System.out.println("initPartTable()");
        this.partTable.setEditable(true);

        InHousePart brakes = new InHousePart(1, "Brakes",15.00, 15, 0, 100);
        InHousePart wheel = new InHousePart(2, "Wheel",11.00, 16, 0, 100);
        InHousePart seat = new InHousePart(3, "Seat",15.00, 10, 0, 100);

        this.parts.add(brakes);
        this.parts.add(wheel);
        this.parts.add(seat);

        TableColumn partIDCol = new TableColumn("Part ID");
        partIDCol.setCellValueFactory(new PropertyValueFactory<>("id"));

        TableColumn partNameCol = new TableColumn("Part Name");
        partNameCol.setCellValueFactory(new PropertyValueFactory<>("name"));

        TableColumn inventoryLevelCol = new TableColumn("Inventory Level");
        inventoryLevelCol.setCellValueFactory(new PropertyValueFactory<>("stock"));

        TableColumn priceCostPerUnitCol = new TableColumn("Price/Cost per Unit");
        priceCostPerUnitCol.setCellValueFactory(new PropertyValueFactory<>("price"));

        partTable.getColumns().addAll(partIDCol, partNameCol, inventoryLevelCol, priceCostPerUnitCol);
        partTable.setItems(this.parts);
    }

    private static boolean productTableInitialized = false;
    public void initProductTable() throws IOException {
        this.productTable.setEditable(true);

        InHousePart brakes = new InHousePart(1, "Brakes",15.00, 15, 0, 100);
        InHousePart wheel = new InHousePart(2, "Wheel",11.00, 16, 0, 100);
        InHousePart seat = new InHousePart(3, "Seat",15.00, 10, 0, 100);

        this.products.add(brakes);
        this.products.add(wheel);
        this.products.add(seat);

        TableColumn productIDCol = new TableColumn("Part ID");
        productIDCol.setCellValueFactory(new PropertyValueFactory<>("id"));

        TableColumn productNameCol = new TableColumn("Part Name");
        productNameCol.setCellValueFactory(new PropertyValueFactory<>("name"));

        TableColumn inventoryLevelCol = new TableColumn("Inventory Level");
        inventoryLevelCol.setCellValueFactory(new PropertyValueFactory<>("stock"));

        TableColumn priceCostPerUnitCol = new TableColumn("Price/Cost per Unit");
        priceCostPerUnitCol.setCellValueFactory(new PropertyValueFactory<>("price"));

        productTable.getColumns().addAll(productIDCol, productNameCol, inventoryLevelCol, priceCostPerUnitCol);
        productTable.setItems(this.products);
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        System.out.println("partTableInitialized: " + this.partTableInitialized);
        if(this.partTableInitialized == false) {
            try {
                initPartTable();
            } catch(Exception e) {
                System.out.println("Error initializing parts table: " + e.toString());
            }
        }
        if(this.productTableInitialized == false) {
            try {
                initProductTable();
            } catch(Exception e) {
                System.out.println("Error initializing products table");
            }
        }

        System.out.println("Initialized");
    }

    public void OnButtonAction(ActionEvent actionEvent) {
        System.out.println("Button Clicked");
        TheLabel.setText("You Clicked!");
    }

    public void toAddPartForm(ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("AddPartForm.fxml"));
        Stage stage = (Stage)((Node)actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root, 600, 400);
        stage.setTitle("Add Part");
        stage.setScene(scene);
        stage.show();
    }

    public void OnDeletePartBtnClicked(ActionEvent actionEvent) {
        System.out.println("OnDeletePartBtnClicked: ");
        Part part = (Part)partTable.getSelectionModel().getSelectedItem();
        System.out.println("part: " + part.getName() + " selected.");

        if(part == null) {
            System.out.println("No part selected.");
            return;
        }
        parts.remove(part);
        partTable.setItems(parts);
    }
}
