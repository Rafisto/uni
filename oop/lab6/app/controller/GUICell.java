package app.controller;

import app.model.ModelCell;
import javafx.application.Platform;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Region;
import javafx.scene.paint.Color;

public class GUICell extends Region {
    private final ModelCell modelCell;
    private Color color;

    /**
     * Returns the ModelCell associated with this GUICell.
     *
     * @return the ModelCell associated with this GUICell
     */
    public final ModelCell getModelCell() {
        return modelCell;
    }

    /**
     * Constructs a new GUICell object with the given ModelCell.
     * 
     * @param modelCell the ModelCell object associated with this GUICell
     */
    public GUICell(ModelCell modelCell) {
        this.modelCell = modelCell;
        this.color = modelCell.getColor();

        setBackground(new Background(new BackgroundFill(color, null, null)));

        modelCell.setGUIRepresentation(this);
    }

    
    /**
     * Runnable that sets the style of the GUICell.
     */
    private final Runnable setStyle = new Runnable() {
        @Override
        public void run() {
            setBackground(new Background(new BackgroundFill(color, null, null)));
        }
    };

    /**
     * Updates the color of the GUICell.
     * If the provided color is not null, it sets the color of the GUICell to the
     * provided color.
     * If the provided color is null, it sets the color of the GUICell to the color
     * of the modelCell.
     * This method should be called on the JavaFX application thread.
     *
     * @param color the color to update the GUICell with
     */
    public final void update(Color color) {
        if (color != null) {
            this.color = color;
        } else {
            this.color = modelCell.getColor();
        }

        Platform.runLater(setStyle);
    }
}
