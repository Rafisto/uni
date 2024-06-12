package app.controller;

import app.logger.AppLogger;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;


/**
 * The GUISimulation class represents a graphical user interface for simulation.
 * It provides methods to set simulation parameters.
 */
public class GUISimulation {
    private double speed;
    private double probability;
    private int width;
    private int height;
    /**
     * Constructs the simulation based on the provided input fields.
     *
     * @param fieldSpeed      the TextField for speed input
     * @param fieldProbability the Slider for probability input
     * @param fieldWidth      the TextField for width input
     * @param fieldHeight     the TextField for height input
     * @param displayPane     the Pane for displaying the simulation
     */
    public GUISimulation(TextField fieldSpeed, Slider fieldProbability, TextField fieldWidth, TextField fieldHeight, Pane displayPane) throws IllegalArgumentException {
        try {
            setParameters(fieldSpeed, fieldProbability, fieldWidth, fieldHeight);
            AppLogger.logger.info("Simulation parameters set successfully");
        } catch (IllegalArgumentException e) {
            System.out.println("Invalid input parameters");
        }

        GUIGrid grid = new GUIGrid(speed, probability, width, height, displayPane);
        AppLogger.logger.info("Grid created successfully");
        
        displayPane.getChildren().add(grid);
    }

    /**
     * Sets the simulation parameters based on the input values.
     *
     * @param fieldSpeed      the TextField containing the speed value
     * @param fieldProbability the Slider containing the probability value
     * @param fieldWidth      the TextField containing the width value
     * @param fieldHeight     the TextField containing the height value
     * @throws IllegalArgumentException if any of the input parameters are invalid
     */
    public void setParameters(TextField fieldSpeed, Slider fieldProbability, TextField fieldWidth, TextField fieldHeight) throws IllegalArgumentException {
        try {
            this.speed = Double.parseDouble(fieldSpeed.getText());
            this.probability = fieldProbability.getValue() / 100.0;
            this.width = Integer.parseInt(fieldWidth.getText());
            this.height = Integer.parseInt(fieldHeight.getText());
            AppLogger.logger.info("Speed: " + speed);
            AppLogger.logger.info("Probability: " + probability);
            AppLogger.logger.info("Width: " + width);
            AppLogger.logger.info("Height: " + height);
        } catch (IllegalArgumentException e) {
            throw new IllegalArgumentException("Invalid input parameters");
        }
    }
}
