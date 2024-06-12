package app.controller;

import app.logger.AppLogger;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;

public class GUIController {
    public GUISimulation guiSimulation;

    @FXML
    private TextField fieldSpeed;

    @FXML
    private TextField fieldHeight;

    @FXML
    private TextField fieldWidth;

    @FXML
    private Slider fieldProbability;

    @FXML
    private Button buttonStart;

    @FXML
    private Button buttonClear;

    @FXML
    private Pane displayPane;

    /**
        * Initializes the GUI Controller.
        * This method is automatically called after the FXML file has been loaded.
        * It sets up the GUI simulation by creating a new instance of GUISimulation
        * with the specified parameters.
        */
    @FXML
    public void initialize() {
        AppLogger.logger.info("Initializing GUI Controller...");
    }

    /**
     * Called when the start button is pressed.
     * Logs an information message indicating that the start button was pressed.
     */
    @FXML
    public void onButtonStartPressed() {
        AppLogger.logger.info("Start button pressed");
        guiSimulation = new GUISimulation(fieldSpeed, fieldProbability, fieldWidth, fieldHeight, displayPane);
    }
}