package app.controller;

import app.model.ModelCell;
import javafx.scene.paint.Color;

/**
 * Represents a GUI cell used for click events in a graphical user interface.
 */
public interface IGUICell {
    /**
     * Returns the ModelCell associated with this IGUICell.
     *
     * @return the ModelCell associated with this IGUICell
     */
    public ModelCell getModelCell();
    /**
     * Updates the color of the cell.
     *
     * @param color the new color for the cell
     */
    public void update(Color color);
}
