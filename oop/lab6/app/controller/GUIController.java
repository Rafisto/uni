package app.controller;

import app.controller.validators.GUIFieldValidator;
import app.logger.AppLogger;
import app.model.ModelGrid;
import app.model.ModelParameters;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.animation.AnimationTimer;

public class GUIController {
    public GUIController() {

    }

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

    @FXML
    public void initialize() {
        AppLogger.logger.info("Initializing GUI Controller...");
    }

    public AnimationTimer GetAnimationTimer() {
        return new AnimationTimer() {
            @Override
            public void handle(long now) {
                if (ModelGrid.getInstance().isRunning()) {
                    GUIGridCreator.UpdateGUIGrid(displayPane);
                }
            }
        };
    }

    @FXML
    public void onButtonStartPressed() {
        AppLogger.logger.info("Start Button Pressed");
        try {
            double speed = GUIFieldValidator.validateSpeed(fieldSpeed.getText());
            double probability = GUIFieldValidator.validateProbability(fieldProbability.getValue());
            int width = GUIFieldValidator.validateWidth(fieldWidth.getText());
            int height = GUIFieldValidator.validateHeight(fieldHeight.getText());
            AppLogger.logger.info("Parameters set: speed=" + speed + ", probability=" + probability + ", width=" + width
                    + ", height=" + height);
            ModelParameters.getInstance().setParameters(speed, probability, width, height);
            ModelGrid.getInstance().Start();
            AppLogger.logger.info("Simulation model started");
            GUIGridCreator.CreateGUIGrid(displayPane);
            AppLogger.logger.info("Grid Created");
            GetAnimationTimer().start();

        } catch (NumberFormatException e) {
            AppLogger.logger.warning("Invalid input: " + e.getMessage());
            return;
        }
    }

    @FXML
    public void onButtonClearPressed() {
        AppLogger.logger.info("Clear Button Pressed");
        // Code to clear the simulation
    }
}