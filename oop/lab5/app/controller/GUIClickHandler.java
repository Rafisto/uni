package app.controller;

import app.controller.GUIMode.Mode;
import app.generator.ShapeGenerator;
import app.logger.AppLogger;
import app.model.IFigure;
import javafx.geometry.Point2D;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.layout.Pane;

public class GUIClickHandler {

    private Point2D initialMousePos;

    
    /** 
     * @param clickEvent
     * @param currentMode
     * @param d
     * @param draw_pane
     * @param selectHandler
     * @param colorPicker
     */
    public void handleLPM(MouseEvent clickEvent, GUIMode currentMode, ShapeGenerator d, Pane draw_pane,
            GUISelect selectHandler, GUIColorPicker colorPicker) {
        initialMousePos = new Point2D(clickEvent.getX(), clickEvent.getY());
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
                    currentMode.switchMode(Mode.VISUAL);
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
            default:
                AppLogger.logger.warning("Unhandled mode");
        }
    }

    public void handleRPM(MouseEvent clickEvent, GUIMode currentMode, ShapeGenerator d, Pane draw_pane,
            GUISelect selectHandler, GUIColorPicker colorPicker) {
        if (currentMode.getCurrentMode() == Mode.SELECT) {
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

    public void handleMouseDrag(MouseEvent dragEvent, GUIMode currentMode, Pane draw_pane,
            GUISelect selectHandler) {
        if (dragEvent.getEventType() == MouseEvent.MOUSE_DRAGGED) {
            if (currentMode.getCurrentMode() == Mode.SELECT) {
                double deltaX = dragEvent.getX() - initialMousePos.getX();
                double deltaY = dragEvent.getY() - initialMousePos.getY();

                selectHandler.getSelectedShape();

                if (selectHandler.getSelectedShape() != null) {
                    selectHandler.getSelectedShape().move(deltaX, deltaY);
                }

                initialMousePos = new Point2D(dragEvent.getX(), dragEvent.getY());
            }
        }
    }

    public void handleScroll(ScrollEvent scrollEvent, GUIMode currentMode, Pane draw_pane, GUISelect selectHandler) {
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