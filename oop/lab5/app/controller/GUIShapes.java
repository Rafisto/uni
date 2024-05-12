package app.controller;

import app.model.IFigureGUI;
import javafx.scene.Node;
import javafx.scene.layout.Pane;

public class GUIShapes {
    public static void SelectShape(Pane pane, IFigureGUI s2) {
        for (Node s : pane.getChildren()) {
            if (s instanceof IFigureGUI) {
                ((IFigureGUI) s).setUnselected();
            }
        }
        s2.setSelected();
    }
    
    public static void UnselectAll(Pane pane) {
        for (Node s : pane.getChildren()) {
            if (s instanceof IFigureGUI) {
                ((IFigureGUI) s).setUnselected();
            }
        }
    }
}
