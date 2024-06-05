package app.controller;

import app.logger.AppLogger;
import app.model.ModelGrid;
import app.model.ModelParameters;
import app.model.ModelSize;
import javafx.event.Event;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class GUIGridCreator {
    public static void CreateGUIGrid(Pane drawPane) {
        for (int i = 0; i < ModelParameters.getInstance().getHeight(); i++) {
            for (int j = 0; j < ModelParameters.getInstance().getWidth(); j++) {
                Rectangle r = new Rectangle();
                r.setY(i * ModelSize.getCellHeight(drawPane));
                r.setX(j * ModelSize.getCellWidth(drawPane));
                r.setWidth(ModelSize.getCellWidth(drawPane));
                r.setHeight(ModelSize.getCellHeight(drawPane));
                r.setFill(Color.RED);

                int id = i * ModelParameters.getInstance().getWidth() + j;
                r.setOnMouseClicked((Event e) -> {
                    (new Thread(() -> {
                        ModelGrid.getInstance().getCell(id).switchRunning();
                    })).start();
                });
                drawPane.getChildren().add(r);
            }
        }
    }

    public static void UpdateGUIGrid(Pane drawPane) {
        for (int i = 0; i < ModelParameters.getInstance().getHeight(); i++) {
            for (int j = 0; j < ModelParameters.getInstance().getWidth(); j++) {
                int id = i * ModelParameters.getInstance().getWidth() + j;
                Color color = ModelGrid.getInstance().getCell(id).getColor();
                Rectangle rectangle = (Rectangle) drawPane.getChildren().get(id);
                if (rectangle != null) {
                    rectangle.setFill(color);
                }
                else {
                    AppLogger.logger.warning("Rectangle with id: " + id + "not found");
                }
            }
        }
    }
}
