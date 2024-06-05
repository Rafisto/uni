package app.model;

import javafx.scene.layout.Pane;

public class ModelSize {
    public static double getCellWidth (Pane drawPane) {
        return drawPane.getWidth() / ModelParameters.getInstance().getWidth();
    }

    public static double getCellHeight (Pane drawPane) {
        return drawPane.getHeight() / ModelParameters.getInstance().getHeight();
    }
}
