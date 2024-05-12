package app.controller;

public class GUIState {
    public enum Mode {
        VISUAL,
        DRAW,
    }
    
    private Mode currentMode;
    
    public GUIState() {
        currentMode = Mode.VISUAL;
    }
    
    public void switchToVisualMode() {
        currentMode = Mode.VISUAL;
        System.out.println("Switched to Visual Mode");
    }
    
    public void switchMode(Mode mode) {
        currentMode = mode;
        System.out.println("Switched to Draw Mode");
    }
    
    public Mode getCurrentMode() {
        return currentMode;
    }
}
