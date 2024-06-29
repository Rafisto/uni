package app.controller;

import app.logger.AppLogger;
import app.model.ModelGrid;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;

public class GUIGrid extends GridPane {

    /**
     * Represents a grid model for the GUI.
     * This class is responsible for managing the grid data and providing methods to interact with it.
     */
    public ModelGrid modelGrid;

    /**
     * Represents a graphical grid that displays cells based on a given speed, probability, width, and height.
     * 
     * @param speed       the speed of the simulation
     * @param probability the probability of a cell being alive
     * @param width       the width of the grid
     * @param height      the height of the grid
     * 
     * @see GUICell
     * @see ModelGrid
     */
    public GUIGrid(double speed, double probability, int width, int height, Pane displayPane) {
        super();
        
        setVgap(0);
        setHgap(0);

        prefWidthProperty().bind(displayPane.widthProperty());
        prefHeightProperty().bind(displayPane.heightProperty());
        setVgrow(displayPane, Priority.ALWAYS);

        setOnMousePressed(this::onModelGridPressed);
        
        AppLogger.logger.info("Creating ModelGrid with speed: " + speed + ", probability: " + probability + ", width: " + width + ", height: " + height);
        modelGrid = new ModelGrid(speed, probability, width, height);
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                AppLogger.logger.fine("Adding GUICell to GUIGrid at row: " + i + ", column: " + j);
                GUICell cell = new GUICell(modelGrid.getCell(i, j));
                modelGrid.getCell(i, j).setGUIRepresentation(cell);
                setHgrow(cell, Priority.ALWAYS);
                setVgrow(cell, Priority.ALWAYS);
                add(cell, j, i);
                AppLogger.logger.fine("GUICell added to GUIGrid at row: " + i + ", column: " + j);
            }
        }

        AppLogger.logger.info("Starting ModelGrid");
        modelGrid.Start();
    }

    /**
     * Event handler for when the draw pane is pressed.
     * 
     * @param e The MouseEvent representing the press event.
     */
    public void onModelGridPressed(MouseEvent e) {
        AppLogger.logger.info("Pressed: " + e.getButton().toString());
        if (e.getButton() == MouseButton.PRIMARY) {
            AppLogger.logger.info("Draw Pane LPM pressed at " + e.getX() + ", " + e.getY());
            GUIClickHandler.handleLPM(e);
        }
    }
}
