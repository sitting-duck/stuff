package inventoryApp;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import static javafx.fxml.FXMLLoader.*;

public class MainController implements Initializable {

    public Label TheLabel;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

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
}
