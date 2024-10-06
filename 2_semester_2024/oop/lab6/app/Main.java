package app;

import javafx.application.Application;
import javafx.stage.Stage;

import app.view.GUI;
import app.logger.AppLogger;

/**
 * The main class of the application.
 * This class extends the JavaFX Application class and is responsible for starting the application.
 */
public class Main extends Application {

    /**
     * The entry point of the application.
     * This method is called when the application is launched.
     * It creates a new instance of the GUI class and passes the primary stage to it.
     *
     * @param primaryStage the primary stage of the application
     */
    @Override
    public void start(Stage primaryStage) {
        new GUI(primaryStage);
    }

    /**
     * The main method of the application.
     * It configures the logger, logs a message, and launches the JavaFX application.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        AppLogger.ConfigureLogger();
        AppLogger.logger.info("Started the app");
        launch(args);
    }
}
