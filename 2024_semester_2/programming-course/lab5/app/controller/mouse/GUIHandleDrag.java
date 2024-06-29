package app.controller.mouse;

import app.controller.GUIMode;
import app.controller.GUIMode.Mode;
import app.logger.AppLogger;
import app.controller.GUISelect;
import javafx.geometry.Point2D;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;

/**
 * Handles the mouse drag event for the selection mode.
 */
public final class GUIHandleDrag {
    /**
    * Handles the mouse drag event for the selection mode.
    * 
    * @param dragEvent      The MouseEvent representing the drag event.
    * @param currentMode    The current GUIMode.
    * @param draw_pane      The Pane where the shapes are drawn.
    * @param selectHandler  The GUISelect object for handling shape selection.
    * @param initialMousePos The initial mouse position when the drag event started.
    */
    public final static void handleMouseDrag(MouseEvent dragEvent, GUIMode currentMode, Pane draw_pane,
            GUISelect selectHandler, GUIMousePosition initialMousePos) {
        if (initialMousePos == null) {
            AppLogger.logger.warning("Initial mouse position is null");
            return;
        }
        if (dragEvent.getEventType() == MouseEvent.MOUSE_DRAGGED) {
            if (currentMode.getCurrentMode() == Mode.SELECT) {
                double deltaX = dragEvent.getX() - initialMousePos.getX();
                double deltaY = dragEvent.getY() - initialMousePos.getY();

                selectHandler.getSelectedShape();

                if (selectHandler.getSelectedShape() != null) {
                    selectHandler.getSelectedShape().move(deltaX, deltaY);
                }

                initialMousePos.setPoint(new Point2D(dragEvent.getX(), dragEvent.getY())); 
            }
        }
    }
}