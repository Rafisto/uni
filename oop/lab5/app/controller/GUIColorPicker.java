package app.controller;

import app.logger.AppLogger;
import app.model.IFigure;
import javafx.scene.control.ColorPicker;
import javafx.scene.layout.Pane;
import javafx.stage.Popup;

/**
 * This class represents a color picker for selecting colors in the GUI.
 */
public final class GUIColorPicker {
    private ColorPicker colorPicker;
    private Popup popup;
    private IFigure target;

    /**
     * Constructs a GUIColorPicker object with the specified GUI mode.
     *
     * @param guiMode the GUI mode to associate with the color picker
     */
    public GUIColorPicker() {
        this.colorPicker = new ColorPicker();
        this.popup = new Popup();
        this.popup.getContent().add(this.colorPicker);

        this.colorPicker.setOnAction(event -> setColor());
    }

    /**
     * Shows the color picker at the specified coordinates on the draw pane.
     *
     * @param x         the x-coordinate of the color picker
     * @param y         the y-coordinate of the color picker
     * @param target    the target figure to apply the color to
     * @param draw_pane the pane on which the color picker is displayed
     */
    public void showColorPicker(double x, double y, IFigure target, Pane draw_pane) {
        this.target = target;
        this.popup.setX(draw_pane.localToScreen(x, y).getX());
        this.popup.setY(draw_pane.localToScreen(x, y).getY());

        this.popup.show(draw_pane.getScene().getWindow());
        this.colorPicker.show();
    }

    /**
     * Sets the color of the target figure to the selected color from the color picker.
     * Hides the color picker and switches the GUI mode to SELECT.
     */
    public void setColor() {
        AppLogger.logger.info("Setting color to: " + this.colorPicker.getValue().toString());
        this.target.setColor(this.colorPicker.getValue().toString());
        hideColorPicker();
    }

    /**
     * Hides the color picker and the associated popup.
     */
    public void hideColorPicker() {
        AppLogger.logger.info("Hiding color picker");
        this.colorPicker.hide();
        this.popup.hide();
    }
}
