package app.controller;

import app.logger.AppLogger;
import javafx.application.Platform;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;

public class GUIClickHandler {
    public final static void handleLPM(MouseEvent clickEvent) {
        if (!clickEvent.isPrimaryButtonDown()) {
            return;
        }

        Node target = (Node) clickEvent.getTarget();
        if (target instanceof IGUICell) {
            IGUICell cell = (IGUICell) target;
            AppLogger.logger.info("Left mouse button pressed on cell " + cell.getModelCell().getId());

            Platform.runLater(() -> {
                cell.getModelCell().changeRunningState();
            });
        }
    }
}
