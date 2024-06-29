package app.controller;

import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;

/**
 * This class represents a GUI popup that displays an error message.
 */
public class GUIPopup {

    /**
     * Constructs a new GUIPopup with the specified owner and error message.
     * 
     * @param owner the owner stage of the popup
     * @param text  the error message to be displayed
     */
    public GUIPopup(Stage owner, String text) {
        Alert alert = new Alert(AlertType.ERROR);
        alert.initOwner(owner);
        alert.setTitle("Error");
        alert.setHeaderText(null);
        alert.setContentText(text);
        alert.showAndWait();
    }
}
