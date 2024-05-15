package app.controller.mouse;

import app.controller.GUIMode;
import app.controller.GUIMode.Mode;
import app.generator.ShapeGenerator;
import app.model.IFigure;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Shape;

public class GUIHandleMouseMoved {
    static IFigure ghost;
    /**
     * Handles the mouse moved event in the GUI.
     * If the current GUI mode is set to DRAW, it removes the previous ghost shape (if any) from the draw pane
     * and creates a new ghost shape based on the mouse position using the given shape generator.
     * If the ghost shape is not null, it adds the ghost shape to the draw pane.
     * If the current GUI mode is not set to DRAW, it removes the previous ghost shape (if any) from the draw pane.
     * 
     * @param mouseEvent the mouse event that triggered the mouse moved event
     * @param guimode the current GUI mode
     * @param draw_pane the pane where the shapes are drawn
     * @param generator the shape generator used to create the ghost shape
     */
    public static void handleMouseMoved(MouseEvent mouseEvent, GUIMode guimode, Pane draw_pane, ShapeGenerator generator)
    {
        if (guimode.getCurrentMode() == Mode.DRAW) 
        {
            draw_pane.getChildren().remove((Shape)ghost);
            ghost = generator.ghostShape(mouseEvent.getX(), mouseEvent.getY());
            
            if (ghost != null) draw_pane.getChildren().add((Shape)ghost);    
        }
        else
            draw_pane.getChildren().remove((Shape)ghost);
    }  
}
