package app.generator;

import java.util.ArrayList;

import app.model.IFigure;
import javafx.geometry.Point2D;

/**
 * The ShapeGenerator interface represents a generator for creating shapes.
 * It provides methods for adding and clearing points, getting the shape type,
 * creating a shape, and checking if the generator is ready.
 */
public interface ShapeGenerator {
    public ArrayList<Point2D> points = new ArrayList<Point2D>();

    /**
     * Adds a point to the shape.
     *
     * @param point2d the point to be added
     */
    public default void addPoint(Point2D point2d) {
        points.add(point2d);
    }

    /**
     * Clears all the points in the shape generator.
     */
    public default void clearPoints() {
        points.clear();
    }

    public String getShapeType();
    public IFigure createShape();
    public IFigure ghostShape(double x, double y);
    public boolean isReady();
}
