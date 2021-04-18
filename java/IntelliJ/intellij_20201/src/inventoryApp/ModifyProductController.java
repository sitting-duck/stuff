package inventoryApp;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.nio.charset.CodingErrorAction;
import java.util.ResourceBundle;

public class ModifyProductController implements Initializable {

    public static Product product;
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



    }

    public static void setProduct(Product _product) {
        product = _product;
    }

    public void saveProduct(ActionEvent actionEvent) throws IOException {
//        String newName = nameTextField.getText();

//        Double newPrice;
//        try {
//            newPrice = Double.parseDouble(priceCostTextField.getText());
//        } catch (NumberFormatException e) {
//            System.out.println("Error parsing Price to Integer: " + priceCostTextField.getText());
//            Alert alert = new Alert(Alert.AlertType.WARNING);
//            alert.setTitle("Invalid Price");
//            alert.setHeaderText("Invalid Price");
//            alert.setContentText("Invalid Price");
//            alert.showAndWait();
//            return;
//        }
//
//        Integer newMin;
//        try {
//            newMin = Integer.parseInt(minTextField.getText());
//        } catch (NumberFormatException e) {
//            System.out.println("Error parsing Min to Integer: " + minTextField.getText());
//            Alert alert = new Alert(Alert.AlertType.WARNING);
//            alert.setTitle("Invalid Min");
//            alert.setHeaderText("Invalid Min");
//            alert.setContentText("Invalid Min");
//            alert.showAndWait();
//            return;
//        }
//
//        Integer newMax;
//        try {
//            newMax = Integer.parseInt(maxTextField.getText());
//        } catch (NumberFormatException e) {
//            System.out.println("Error parsing Max to Integer: " + maxTextField.getText());
//            Alert alert = new Alert(Alert.AlertType.WARNING);
//            alert.setTitle("Invalid Max");
//            alert.setHeaderText("Invalid Max");
//            alert.setContentText("Invalid Max");
//            alert.showAndWait();
//            return;
//        }
//
//        Integer newStock;
//        try {
//            newStock = Integer.parseInt(invTextField.getText());
//        } catch (NumberFormatException e) {
//            System.out.println("Error parsing Inventory/Stock to Integer: " + invTextField.getText());
//            Alert alert = new Alert(Alert.AlertType.WARNING);
//            alert.setTitle("Invalid Inv");
//            alert.setHeaderText("Invalid Inv");
//            alert.setContentText("Invalid Inv");
//            alert.showAndWait();
//            return;
//        }
//
//        int newMachineId = -1;
//        String newCompanyName = "";
//        if(part instanceof InHousePart) {
//            try {
//                newMachineId = Integer.parseInt(bottomTextField.getText());
//            } catch (NumberFormatException e) {
//                System.out.println("Error parsing machineId to Integer: " + bottomTextField.getText());
//                Alert alert = new Alert(Alert.AlertType.WARNING);
//                alert.setTitle("Invalid Machine ID");
//                alert.setHeaderText("Invalid Machine ID");
//                alert.setContentText("Invalid Machine ID");
//                alert.showAndWait();
//                return;
//            }
//
//        } else if(part instanceof OutSourcedPart) {
//            newCompanyName = bottomTextField.getText();
//        }
//        System.out.println("partOriginal before delete: " + partOriginal.getName());
//        System.out.println("Result of deletePart(): " + inventory.deletePart(partOriginal));
//
//        part.setName(newName);
//        part.setPrice(newPrice);
//        part.setMin(newMin);
//        part.setMax(newMax);
//        part.setStock(newStock);
//        if(part instanceof InHousePart) {
//            ((InHousePart)part).setMachineId(newMachineId);
//        } else if(part instanceof OutSourcedPart) {
//            ((OutSourcedPart)part).setCompanyName(newCompanyName);
//        }
//        inventory.addPart(part);
//
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
}
