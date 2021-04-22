package inventoryApp;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class AddPartController implements Initializable {

    public static boolean initialized = false;
    public TextField idTextField;
    public TextField nameTextField;
    public TextField invTextField;
    public TextField priceTextField;
    public TextField minTextField;
    public TextField maxTextField;
    public TextField bottomTextField;
    public Label bottomTextFieldLabel;

    public RadioButton inHouseRadioButton;
    public RadioButton outsourcedRadioButton;

    private static Inventory inventory = new Inventory();

    private ToggleGroup toggleGroup = new ToggleGroup();

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        idTextField.setText(Integer.toString(inventory.newPartId()));
        idTextField.setEditable(false);
        idTextField.setDisable(true);

        inHouseRadioButton.setSelected(true);
        inHouseRadioButton.setToggleGroup(toggleGroup);
        outsourcedRadioButton.setToggleGroup(toggleGroup);

        invTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    invTextField.setText(newValue.replaceAll("[^\\d]", ""));
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
        bottomTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    bottomTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });
    }

    public void toMainForm(ActionEvent actionEvent) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("MainForm.fxml"));
        Stage stage = (Stage) ((Button)actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root, 600, 400);
        stage.setTitle("MainForm");
        stage.setScene(scene);
        stage.show();
    }

    public void setLabelToMachineID(ActionEvent actionEvent) {
        System.out.println("setLabelToMachineID");
        bottomTextFieldLabel.setText("Machine ID");
    }

    public void setLabelToCompanyName(ActionEvent actionEvent) {
        System.out.println("setLabelToCompanyName");
        bottomTextFieldLabel.setText("Company Name");
    }

    public void savePart(ActionEvent actionEvent) throws IOException {
        System.out.println("savePart()");
        String newName = nameTextField.getText();

        if(newName.length() == 0) {
            System.out.println("Error Invalid Name: " + newName);
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Invalid Name");
            alert.setHeaderText("Invalid Name");
            alert.setContentText("Invalid Name");
            alert.showAndWait();
            return;
        }

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

        int newMachineId = -1;
        String newCompanyName = "";
        if(inHouseRadioButton.isSelected()) {
            try {
                newMachineId = Integer.parseInt(bottomTextField.getText());
            } catch (NumberFormatException e) {
                System.out.println("Error parsing machineId to Integer: " + bottomTextField.getText());
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Invalid Machine ID");
                alert.setHeaderText("Invalid Machine ID");
                alert.setContentText("Invalid Machine ID");
                alert.showAndWait();
                return;
            }
            InHousePart part = new InHousePart(Integer.parseInt(idTextField.getText()), newName, newPrice, newStock, newMin, newMax, newMachineId);
            inventory.addPart(part);
            System.out.println("Add InHouse Part: " + part.getName());
        } else if(outsourcedRadioButton.isSelected()) {
            newCompanyName = bottomTextField.getText();
            OutSourcedPart part = new OutSourcedPart(Integer.parseInt(idTextField.getText()), newName, newPrice, newStock, newMin, newMax, newCompanyName);
            inventory.addPart(part);
            System.out.println("Add Outsourced Part: " + part.getName());
        }
        toMainForm(actionEvent);
    }
}
