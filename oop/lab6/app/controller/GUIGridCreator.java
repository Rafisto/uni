package app.controller;

import app.model.ModelParameters;
import javafx.scene.layout.Pane;

public class GUIGridCreator {
    public GUIGridCreator(Pane drawPane) {
        for (int i = 0; i < ModelParameters.getInstance().getHeight(); i++) {
            for (int j = 0; j < ModelParameters.getInstance().getWidth(); j++) {
                drawPane.getChildren().add(new GUICell(i, j));
            }
        }
    }
}
