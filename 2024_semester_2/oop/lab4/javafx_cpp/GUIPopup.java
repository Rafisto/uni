import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;

public class GUIPopup {

    public GUIPopup(Stage owner, String text) {
        AppLogger.logger.warning("Displaying popup error: " + text);
        Alert alert = new Alert(AlertType.ERROR);
        alert.initOwner(owner);
        alert.setTitle("Error");
        alert.setHeaderText(null);
        alert.setContentText(text);
        alert.showAndWait();
    }
}