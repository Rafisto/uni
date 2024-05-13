package app.model;

import java.io.Serializable;
import java.util.ArrayList;

import javafx.geometry.Point2D;

public interface IFigure extends IFigurePhysics, IFigureGUI, Serializable {
    ArrayList<Point2D> points = new ArrayList<Point2D>();
    double scale  = 1;
    double rotate = 0;
    String color = "#000000";
}