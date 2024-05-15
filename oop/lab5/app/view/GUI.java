package app.view;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.io.IOException;

import app.controller.GUIController;
import app.logger.AppLogger;

/**
 * The GUI class represents the graphical user interface of the application.
 * It is responsible for initializing and displaying the main window of the Shape Editor.
 */
public class GUI {
    /**
     * Constructs a new GUI object with the specified primaryStage.
     *
     * @param primaryStage the primary stage of the JavaFX application
     */
    public GUI(Stage primaryStage) {
        try {
            AppLogger.logger.info("Initializing GUI...");

            FXMLLoader loader = new FXMLLoader(getClass().getResource("app.fxml"));

            GUIController controller = (GUIController) new GUIController();

            Parent root = loader.load();
            Scene scene = new Scene(root);

            controller.initialize();

            primaryStage.setScene(scene);
            primaryStage.setTitle("Paint it Black!");
            primaryStage.show();

            AppLogger.logger.info("GUI initialized successfully");
        } catch (IOException e) {
            AppLogger.logger.severe("IOError initializing GUI: " + e.getMessage());
        } catch (Exception e) {
            AppLogger.logger.severe("Error initializing GUI: " + e.getMessage());
        }
    }
}
