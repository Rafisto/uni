package app.controller;

public class AppState {
    public enum Mode {
        VISUAL,
        DRAW
    }
    
    private Mode currentMode;
    
    public AppState() {
        currentMode = Mode.VISUAL;
    }
    
    public void switchToVisualMode() {
        currentMode = Mode.VISUAL;
        System.out.println("Switched to Visual Mode");
    }
    
    public void switchToDrawMode() {
        currentMode = Mode.DRAW;
        System.out.println("Switched to Draw Mode");
    }
    
    public Mode getCurrentMode() {
        return currentMode;
    }
}
