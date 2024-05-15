package app.controller;

import app.logger.AppLogger;

/**
 * The GUIMode class represents the mode of the GUI application.
 * It allows switching between different modes such as visual, draw, select, and color.
 */
public class GUIMode {
    /**
     * The Mode enum represents the different modes of the GUI application.
     * It includes the modes: visual, draw, select, and color.
     */
    public enum Mode {
        VISUAL,
        DRAW,
        SELECT,
        COLOR
    }
    
    private GUIController controller;
    private Mode currentMode;
    
    /**
     * Constructs a GUIMode object with the specified GUIController.
     * The initial mode is set to visual.
     * 
     * @param controller the GUIController object
     */
    public GUIMode(GUIController controller) {
        this.controller = controller;
        currentMode = Mode.VISUAL;
    }
    
    /**
     * Switches the mode of the GUI application to the specified mode.
     * It updates the mode label in the GUIController and logs the mode switch.
     * 
     * @param mode the mode to switch to
     */
    public void switchMode(Mode mode) {
        currentMode = mode;
        controller.updateModeLabel();
        AppLogger.logger.info("Switching mode to " + mode);
    }
    
    /**
     * Returns the current mode of the GUI application.
     * 
     * @return the current mode
     */
    public Mode getCurrentMode() {
        return currentMode;
    }   
}
