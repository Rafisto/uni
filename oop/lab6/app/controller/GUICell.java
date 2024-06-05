package app.controller;

import app.model.ModelCell;
import app.model.ModelGrid;
import app.model.ModelSize;
import javafx.event.Event;
import javafx.scene.shape.Rectangle;

public class GUICell extends Rectangle {
    private ModelCell cell;

    public GUICell(int i, int j) {
        this.cell = ModelGrid.getInstance().getCell(i,j);
        Rectangle r = new Rectangle();

        r.setOnMouseClicked((Event e) -> {
            (new Thread(()->{
                int id = Integer.parseInt(((Rectangle) e.getSource()).getId());
                ModelGrid.getInstance().getCell(id).switchRunning();
            })).start();
        });
    }
}
