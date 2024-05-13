package app.controller;

import app.controller.GUIMode.Mode;
import app.logger.AppLogger;
import app.model.IFigure;
import javafx.scene.control.ColorPicker;
import javafx.scene.layout.Pane;
import javafx.stage.Popup;

public class GUIColorPicker {
    private ColorPicker colorPicker;
    private GUIMode guiMode;
    private Popup popup;
    private IFigure target;

    public GUIColorPicker(GUIMode guiMode) {
        this.colorPicker = new ColorPicker();
        this.popup = new Popup();
        this.popup.getContent().add(this.colorPicker);

        this.colorPicker.setOnAction(event -> setColor());
    }

    
    /** 
     * @param x
     * @param y
     * @param target
     * @param draw_pane
     */
    public void showColorPicker(double x, double y, IFigure target, Pane draw_pane) {
        this.target = target;
        this.popup.setX(draw_pane.localToScreen(x, y).getX());
        this.popup.setY(draw_pane.localToScreen(x, y).getY());
    
        this.popup.show(draw_pane.getScene().getWindow());
        this.colorPicker.show();
    }

    public void setColor() {
        AppLogger.logger.info("Setting color to: " + this.colorPicker.getValue().toString());
        this.target.setColor(this.colorPicker.getValue().toString());
        hideColorPicker();
        this.guiMode.switchMode(Mode.SELECT);
    }

    public void hideColorPicker() {
        AppLogger.logger.info("Hiding color picker");
        this.colorPicker.hide();
        this.popup.hide();
    }
}
