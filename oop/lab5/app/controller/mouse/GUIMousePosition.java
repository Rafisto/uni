package app.controller.mouse;

import javafx.geometry.Point2D;

/**
 * The GUIMousePosition class represents the position of the mouse in a GUI.
 */
public final class GUIMousePosition {
    private Point2D point;

    /**
     * Constructs a GUIMousePosition object with the specified point.
     *
     * @param point the point representing the mouse position
     */
    public GUIMousePosition(Point2D point) {
        this.point = point;
    }

    /**
     * Returns the point representing the mouse position.
     *
     * @return the point representing the mouse position
     */
    public Point2D getPoint() {
        return point;
    }

    /**
     * Sets the point representing the mouse position.
     *
     * @param point the point representing the mouse position
     */
    public void setPoint(Point2D point) {
        this.point = point;
    }

    /**
     * Returns the x-coordinate of the mouse position.
     *
     * @return the x-coordinate of the mouse position
     */
    public double getX() {
        return point.getX();
    }

    /**
     * Returns the y-coordinate of the mouse position.
     *
     * @return the y-coordinate of the mouse position
     */
    public double getY() {
        return point.getY();
    }

    /**
     * Sets the x-coordinate of the mouse position.
     *
     * @param x the x-coordinate of the mouse position
     */
    public void setX(double x) {
        this.point = new Point2D(x, this.point.getY());
    }

    /**
     * Sets the y-coordinate of the mouse position.
     *
     * @param y the y-coordinate of the mouse position
     */
    public void setY(double y) {
        this.point = new Point2D(this.point.getX(), y);
    }
}