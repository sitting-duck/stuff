package inventoryApp;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.stage.Stage;


import java.io.IOException;

//import static jdk.vm.ci.aarch64.AArch64.v1;

public class Main extends Application {



    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("MainForm.fxml"));
        primaryStage.setTitle("Hello World");
        Scene scene = new Scene(root, 600, 400);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public void toSecond(ActionEvent actionEvent) throws IOException {
        //load widget hierarchy of next screen
        Stage stage = (Stage)((Node)actionEvent.getSource()).getScene().getWindow();

        // Create the new scene
        //Scene scene = new Scene(root, v: 600, v1: 400);
        //stage.setTitle("Second Screen");

        // Set the scene on the stage
        //stage.setScene(scene);

        //raise the curtain
        //stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
