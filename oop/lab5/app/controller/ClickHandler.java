package app.controller;

import javafx.scene.input.MouseEvent;

public class ClickHandler {
    public void handleLPM(MouseEvent clickEvent, AppState currentMode, Drawer d) {
        switch(currentMode.getCurrentMode()) {
            case VISUAL:
                System.out.println("No action in VISUAL mode");
                break;
            case DRAW:
                System.out.println("Draw shape");
                d.addPoint(clickEvent.getX(), clickEvent.getY());
                break;
            default:
                System.out.println("Unknown mode");
        }
    }
}
