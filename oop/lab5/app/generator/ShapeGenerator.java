package app.generator;

import java.util.ArrayList;

import app.model.IFigure;
import javafx.geometry.Point2D;

public interface ShapeGenerator {
    public ArrayList<Point2D> points = new ArrayList<Point2D>();

    public default void addPoint(Point2D point2d) {
        points.add(point2d);
    }

    public default void clearPoints() {
        points.clear();
    }

    public String getShapeType();
    public IFigure createShape();
    public boolean isReady();
}
