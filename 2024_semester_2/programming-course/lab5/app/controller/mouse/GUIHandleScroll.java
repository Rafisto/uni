package app.controller.mouse;

import app.controller.GUIMode;
import app.controller.GUIMode.Mode;
import app.controller.GUISelect;
import javafx.scene.input.ScrollEvent;
import javafx.scene.layout.Pane;

/**
 * This class handles the scroll event in the GUI.
 */
public final class GUIHandleScroll {
    /**
     * Handles the scroll event in the GUI.
     *
     * @param scrollEvent   The scroll event.
     * @param currentMode   The current GUI mode.
     * @param draw_pane     The pane where the shapes are drawn.
     * @param selectHandler The handler for shape selection.
     */
    public final static void handleScroll(ScrollEvent scrollEvent, GUIMode currentMode, Pane draw_pane, GUISelect selectHandler) {
        if (selectHandler.getSelectedShape() == null || currentMode.getCurrentMode() != Mode.SELECT) {
            return;
        }

        boolean isCtrlPressed = scrollEvent.isControlDown();

        if (isCtrlPressed) {
            double deltaY = scrollEvent.getDeltaY();
            if (deltaY > 0) {
                selectHandler.getSelectedShape().scale(1.1);
            } else if (deltaY < 0) {
                selectHandler.getSelectedShape().scale(0.9);
            }
        } else {
            double deltaY = scrollEvent.getDeltaY();
            selectHandler.getSelectedShape().rotate(deltaY * 0.1);
        }
    }
}
