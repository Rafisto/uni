package app.view;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

/**
 * The INFO class provides a utility method to display an information popup
 * dialog.
 */
public class INFO {
    /**
     * Displays an information popup dialog with the specified message.
     *
     * @param message the message to be displayed in the popup dialog
     */
    public static void showInfoPopup(String message) {
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle("Information");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    /**
     * Displays a popup dialog with the content of the instruction.txt file.
     */
    public static void showInstructionPopup() {
        try {
            Path filePath = Paths.get("instruction.txt");
            byte[] content = Files.readAllBytes(filePath);

            ScrollPane scrollPane = new ScrollPane();
            scrollPane.setFitToWidth(true);
            scrollPane.setFitToHeight(true);

            VBox vBox = new VBox();
            vBox.getChildren().add(new Text(new String(content)));

            scrollPane.setContent(vBox);

            Alert alert = new Alert(AlertType.INFORMATION);
            alert.setTitle("Instruction");
            alert.setHeaderText(null);
            alert.getDialogPane().setContent(scrollPane);
            alert.showAndWait();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
