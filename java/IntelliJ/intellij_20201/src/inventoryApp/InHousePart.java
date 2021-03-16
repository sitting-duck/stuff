package inventoryApp;

import javafx.fxml.Initializable;

import java.net.URL;
import java.util.ResourceBundle;

public class InHousePart extends Part {
    public InHousePart(int id, String name, double price, int stock, int min, int max) {
        super(id, name, price, stock, min, max);
    }
}
