package inventoryApp;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.Initializable;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;

import java.net.URL;
import java.util.ResourceBundle;

public class ModifyProductController implements Initializable {

    public static Product product;

    public TextField idTextField;
    public TextField nameTextField;
    public TextField priceCostTextField;
    public TextField minTextField;
    public TextField maxTextField;
    public TextField machineIdTextField;

    private ToggleGroup toggleGroup = new ToggleGroup();
    public RadioButton outsourcedRadioButton;
    public RadioButton inHouseRadioButton;

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
        outsourcedRadioButton.setToggleGroup(toggleGroup);

        idTextField.setText(Integer.toString(product.getId()));
        idTextField.setEditable(false);
        nameTextField.setText(product.getName());
        priceCostTextField.setText(Double.toString(product.getPrice()));
        maxTextField.setText(Double.toString(product.getMax()));
        minTextField.setText(Double.toString(product.getMin()));
    }

    public static void setProduct(Product _product) {
        product = _product;
    }
}
