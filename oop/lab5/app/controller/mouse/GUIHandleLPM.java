package app.controller.mouse;

import app.controller.GUIColorPicker;
import app.controller.GUIMode;
import app.controller.GUIMode.Mode;
import app.controller.GUISelect;
import app.generator.ShapeGenerator;
import app.logger.AppLogger;
import app.model.IFigure;
import javafx.geometry.Point2D;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;

/**
 * This class handles the Left Mouse Button Press (LPM) event in the GUI.
 */
public class GUIHandleLPM {
    /**
     * Handles the Left Mouse Button Press (LPM) event in the GUI.
     * 
     * @param clickEvent      The MouseEvent representing the LPM event.
     * @param currentMode     The current GUIMode.
     * @param d               The ShapeGenerator for creating shapes.
     * @param draw_pane       The Pane where the shapes are drawn.
     * @param selectHandler   The GUISelect object for handling shape selection.
     * @param colorPicker     The GUIColorPicker object for selecting colors.
     * @param initialMousePos The initial mouse position when the LPM event started.
     */
    public static void handleLPM(MouseEvent clickEvent, GUIMode currentMode, ShapeGenerator d, Pane draw_pane,
            GUISelect selectHandler, GUIColorPicker colorPicker, GUIMousePosition initialMousePos) {
        initialMousePos.setPoint(new Point2D(clickEvent.getX(), clickEvent.getY()));
        Node target = (Node) clickEvent.getTarget();
        switch (currentMode.getCurrentMode()) {
            case VISUAL:
                if (target instanceof IFigure) {
                    if (clickEvent.isControlDown()) {
                        AppLogger.logger.info("Ctrl + Clicked on a figure: " + target.getClass().getName());
                        AppLogger.logger.info("Deleting shape");
                        draw_pane.getChildren().remove((Node) target);
                        selectHandler.UnselectAll(draw_pane);
                    } else {
                        AppLogger.logger.info("Clicked on a figure: " + target.getClass().getName());
                        AppLogger.logger.info("Selecting shape");
                        selectHandler.SelectShape(draw_pane, (IFigure) target);
                        currentMode.switchMode(Mode.SELECT);
                    }
                } else {
                    AppLogger.logger.info("No pane action in VISUAL mode");
                    AppLogger.logger.info("Unselecting shapes");
                    selectHandler.UnselectAll(draw_pane);
                }
                break;
            case DRAW:
                AppLogger.logger.info("Draw mode");
                d.addPoint(new Point2D(clickEvent.getX(), clickEvent.getY()));
                if (d.isReady()) {
                    selectHandler.UnselectAll(draw_pane);
                    draw_pane.getChildren().add((Node) d.createShape());
                    d.clearPoints();
                    if (clickEvent.isControlDown()) {
                        AppLogger.logger.info("Ctrl + Left Mouse Button Pressed in DRAW mode");
                        AppLogger.logger.info("Not exiting draw mode");
                    } else {
                        currentMode.switchMode(Mode.VISUAL);
                    }
                }
                break;
            case SELECT:
                AppLogger.logger.info("Select mode");
                if (target instanceof IFigure) {
                    AppLogger.logger.info("Clicked on a figure: " + target.getClass().getName());
                    AppLogger.logger.info("Selecting a new shape");
                    selectHandler.SelectShape(draw_pane, (IFigure) target);
                } else {
                    AppLogger.logger.info("Unselecting shapes");
                    selectHandler.UnselectAll(draw_pane);
                    currentMode.switchMode(Mode.VISUAL);
                }
                break;
            case COLOR:
                AppLogger.logger.info("Color mode");
                if (!(target instanceof IFigure)) {
                    AppLogger.logger.info("Exiting color mode");
                    selectHandler.UnselectAll(draw_pane);
                    colorPicker.hideColorPicker();
                    currentMode.switchMode(Mode.VISUAL);
                }
                else {
                    AppLogger.logger.info("Clicked on a figure: " + target.getClass().getName());
                    AppLogger.logger.info("Selecting a new shape");
                    selectHandler.SelectShape(draw_pane, (IFigure) target);
                }
            default:
                AppLogger.logger.info("Unhandled mode");
        }
    }
}