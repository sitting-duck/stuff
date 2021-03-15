### Change Scenes
```
// get the stage from any widget declared in the controller
Stage stage - (Stage) cancelButton.getScene().getWindow();

// You could also get the stage via the widget of an action event
Stage stage = (Stage) ((Node)event.getSource()).getScene().getWindow();

```

### Full Scene Change on the Stage
```
public void toSecond(ActionEvent actionEvent) throws IOException {
	// load widget hierarchy of next screen
	Parent root = FXMLLoader.load(getClass().getResource("/view/Second.fxml"));
	
	// get the stage from an events source widget
	Stage stage = (Stage) ((Node)actionEvent.getSource()).getScene().getWindow();

	// Create the new Scene
	Scene scene = new Scene(root, 600, 400);
	Stage.setTitle("Second Screen");

	//Set the scene on the stage
	stage.setScene(scene);
	stage.show();


}
```
