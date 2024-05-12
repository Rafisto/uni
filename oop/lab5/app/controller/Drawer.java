package app.controller;

import javafx.scene.layout.Pane;
import javafx.scene.shape.Shape;

public class Drawer {
    public void DrawShape(Pane pane, Shape shape) {
        pane.getChildren().add(shape);
    }
}
