package inventoryApp;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class ModifyPartController implements Initializable {

    public static Part part;
    public static Part partOriginal;

    public TextField idTextField;
    public TextField nameTextField;
    public TextField priceCostTextField;
    public TextField minTextField;
    public TextField maxTextField;
    public TextField invTextField;
    public TextField bottomTextField;

    public Button cancelBtn;
    public Button saveBtn;


    private ToggleGroup toggleGroup = new ToggleGroup();
    public RadioButton outsourcedRadioButton;
    public RadioButton inHouseRadioButton;

    private static Inventory inventory = new Inventory();

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        if(part instanceof InHousePart) {
            System.out.println("Part is InHousePart");
            partOriginal = new InHousePart(part.getId(), part.getName(), part.getPrice(), part.getStock(), part.getMin(), part.getMax(), ((InHousePart) part).getMachineId());
        } else if(part instanceof OutSourcedPart) {
            System.out.println("Part is OutsourcedPart");
            partOriginal = new OutSourcedPart(part.getId(), part.getName(), part.getPrice(), part.getStock(), part.getMin(), part.getMax(), ((OutSourcedPart) part).getCompanyName());
        }
        //partOriginal = new Part(part.getId(), part.getName(), part.getPrice(), part.getStock(), part.getMin(), part.getMax());
        partOriginal.setId(part.getId());
        partOriginal.setName(part.getName());
        partOriginal.setMin(part.getMin());
        partOriginal.setMax(part.getMax());
        partOriginal.setPrice(part.getPrice());
        partOriginal.setStock(part.getStock());

        idTextField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(!newValue.matches("\\d*")) {
                    idTextField.setText(newValue.replaceAll("[^\\d]", ""));
                }
            }
        });
        inHouseRadioButton.setToggleGroup(toggleGroup);
        outsourcedRadioButton.setToggleGroup(toggleGroup);

        idTextField.setText(Integer.toString(part.getId()));
        idTextField.setEditable(false);
        idTextField.setDisable(true);
        nameTextField.setText(part.getName());
        priceCostTextField.setText(Double.toString(part.getPrice()));
        maxTextField.setText(Double.toString(part.getMax()));
        minTextField.setText(Double.toString(part.getMin()));
        invTextField.setText(Integer.toString(part.getStock()));
    }

    public void savePart(ActionEvent actionEvent) throws IOException {
        System.out.println("Result of delet: " + inventory.deletePart(partOriginal));
        inventory.addPart(part);
        toMainForm(actionEvent);
    }

    public void toMainForm(ActionEvent actionEvent) throws IOException {
        if(outsourcedRadioButton.isSelected()) {
            System.out.println("Outsourced");
        }
        if(inHouseRadioButton.isSelected()) {
            System.out.println("In House");
        }

        Parent root = FXMLLoader.load(getClass().getResource("MainForm.fxml"));
        Stage stage = (Stage) ((Button)actionEvent.getSource()).getScene().getWindow();
        Scene scene = new Scene(root, 600, 400);
        stage.setTitle("MainForm");
        stage.setScene(scene);
        stage.show();
    }

    public static void setPart(Part _part) {
        part = _part;
    }
}
