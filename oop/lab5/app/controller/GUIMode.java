package app.controller;

import app.logger.AppLogger;

public class GUIMode {
    public enum Mode {
        VISUAL,
        DRAW,
        SELECT
    }
    
    private GUIController controller;
    private Mode currentMode;
    
    public GUIMode(GUIController controller) {
        this.controller = controller;
        currentMode = Mode.VISUAL;
    }
    
    public void switchMode(Mode mode) {
        currentMode = mode;
        controller.updateModeLabel();
        AppLogger.logger.info("Switching mode to " + mode);
    }
    
    public Mode getCurrentMode() {
        return currentMode;
    }   
}
