package app.controller;

import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;

public class GUIClickHandler {
    public void handleLPM(MouseEvent clickEvent, GUIState currentMode, Drawer d, Pane draw_pane) {
        switch(currentMode.getCurrentMode()) {
            case VISUAL:
                System.out.println("No action in VISUAL mode");
                break;
            case DRAW:
                System.out.println("Draw shape");
                d.addPoint(clickEvent.getX(), clickEvent.getY());
                if (d.isReady()) {
                    d.drawShape(draw_pane);
                    currentMode.switchToVisualMode();
                }
                break;
            default:
                System.out.println("Unknown mode");
        }
    }
}
