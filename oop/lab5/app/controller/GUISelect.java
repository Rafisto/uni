package app.controller;

import app.model.IFigure;
import javafx.scene.Node;
import javafx.scene.layout.Pane;

public final class GUISelect {
    private IFigure selectedShape;

    public GUISelect() {}

    /**
     * Selects the specified shape in the given pane.
     * 
     * This method iterates through all the nodes in the pane and sets the selected state to false for all IFigure instances.
     * Then, it sets the selected state of the specified shape to true and updates the selectedShape property.
     * 
     * @param pane The pane containing the shapes.
     * @param s2 The shape to be selected.
     */
    public final void SelectShape(Pane pane, IFigure s2) {
        for (Node s : pane.getChildren()) {
            if (s instanceof IFigure) {
                ((IFigure) s).setUnselected();
            }
        }
        s2.setSelected();
        selectedShape = s2;
    }
    
    /**
     * Unselects all shapes in the given pane.
     * 
     * This method iterates through all the nodes in the pane and sets the selected state to false for all IFigure instances.
     * 
     * @param pane The pane containing the shapes.
     */
    public final void UnselectAll(Pane pane) {
        for (Node s : pane.getChildren()) {
            if (s instanceof IFigure) {
                ((IFigure) s).setUnselected();
            }
        }
    }

    /**
     * Returns the currently selected shape.
     * 
     * @return The currently selected shape.
     */
    public final IFigure getSelectedShape() {
        return selectedShape;
    }
}
