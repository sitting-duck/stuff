package inventoryApp;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class AddPartController implements Initializable {

    public static boolean initialized = false;
    public TableView addTestData() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("AddPartForm.fxml"));
        Scene scene = new Scene(root, 600, 400);
        TableView partTableView = (TableView) scene.lookup("#partTable");
        partTableView.setEditable(true);

        InHousePart brakes = new InHousePart(1, "Brakes",15.00, 15, 0, 100);
        InHousePart wheel = new InHousePart(2, "Wheel",11.00, 16, 0, 100);
        InHousePart seat = new InHousePart(3, "Seat",15.00, 10, 0, 100);

        TableColumn partIDCol = new TableColumn("Part ID");
        TableColumn partNameCol = new TableColumn("Part Name");
        TableColumn inventoryLevelCol = new TableColumn("Inventory Level");
        TableColumn priceCostPerUnitCol = new TableColumn("Price/Cost per Unit");

        partTableView.getColumns().addAll(partIDCol, partNameCol, inventoryLevelCol, priceCostPerUnitCol);

        final ObservableList<InHousePart> inHousePartsList = FXCollections.observableArrayList(brakes, wheel, seat);
        this.initialized = true;
        return partTableView;
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        //if(this.initialized == false) {
        //   try {
        //        addTestData();
        //    } catch(Exception e) {
        //        System.out.println("Error while initializing table data.");
        //    }

        //}
        System.out.println("after");
        //InHousePart brakes = new InHousePart(1, "Brakes",15.00, 15, 0, 100);
        //InHousePart wheel = new InHousePart(2, "Wheel",11.00, 16, 0, 100);
        //InHousePart seat = new InHousePart(3, "Seat",15.00, 10, 0, 100);
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
