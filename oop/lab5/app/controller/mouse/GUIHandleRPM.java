package app.controller.mouse;

import app.controller.GUIColorPicker;
import app.controller.GUIMode;
import app.controller.GUIMode.Mode;
import app.controller.GUISelect;
import app.generator.ShapeGenerator;
import app.logger.AppLogger;
import app.model.IFigure;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;

/**
 * This class handles the RPM (Right-Click Pressed) event in the GUI.
 */
public class GUIHandleRPM {
    /**
     * Handles the RPM event by performing specific actions based on the current GUI mode.
     * If the current mode is SELECT, it selects the clicked node and shows a color picker.
     * Then, it switches the mode to COLOR.
     *
     * @param clickEvent    The MouseEvent representing the RPM event.
     * @param currentMode   The current GUI mode.
     * @param d             The ShapeGenerator used for generating shapes.
     * @param draw_pane     The Pane where the shapes are drawn.
     * @param selectHandler The GUISelect handler for selecting nodes.
     * @param colorPicker   The GUIColorPicker for choosing colors.
     */
    public static void handleRPM(MouseEvent clickEvent, GUIMode currentMode, ShapeGenerator d, Pane draw_pane,
                                 GUISelect selectHandler, GUIColorPicker colorPicker) {
        if (currentMode.getCurrentMode() == Mode.SELECT || currentMode.getCurrentMode() == Mode.COLOR) {
            Node target = (Node) clickEvent.getTarget();
            AppLogger.logger.info("Selected node: " + target.toString());
            double x = clickEvent.getX();
            double y = clickEvent.getY();

            if (target instanceof IFigure) {
                colorPicker.showColorPicker(x, y, (IFigure) target, draw_pane);
            }
            currentMode.switchMode(Mode.COLOR);
        }
    }
}