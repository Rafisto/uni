package app.model;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import javafx.scene.paint.Color;

/**
 * Represents a custom rectangle shape that implements the IFigure interface.
 */
public class MyRectangle extends javafx.scene.shape.Rectangle implements IFigure {

    /**
     * Constructs a new MyRectangle object with the specified coordinates.
     *
     * @param x1 the x-coordinate of the first point
     * @param y1 the y-coordinate of the first point
     * @param x2 the x-coordinate of the second point
     * @param y2 the y-coordinate of the second point
     */
    public MyRectangle(double x1, double y1, double x2, double y2) {
        super();
        double topLeftX = Math.min(x1, x2);
        double topLeftY = Math.min(y1, y2);
        double bottomRightX = Math.max(x1, x2);
        double bottomRightY = Math.max(y1, y2);

        setX(topLeftX);
        setY(topLeftY);
        setWidth(bottomRightX - topLeftX);
        setHeight(bottomRightY - topLeftY);
    }

    /**
     * Scales the rectangle by the specified factor.
     *
     * @param scaleFactor the scaling factor
     */
    @Override
    public void scale(double scaleFactor) {
        setWidth(scaleFactor * getWidth());
        setHeight(scaleFactor * getHeight());
    }

    /**
     * Moves the rectangle by the specified deltas.
     *
     * @param deltaX the change in x-coordinate
     * @param deltaY the change in y-coordinate
     */
    @Override
    public void move(double deltaX, double deltaY) {
        setX(getX() + deltaX);
        setY(getY() + deltaY);
    }

    /**
     * Rotates the rectangle by the specified angle.
     *
     * @param angle the rotation angle in degrees
     */
    @Override
    public void rotate(double angle) {
        setRotate(getRotate() + angle);
    }

    /**
     * Sets the fill color of the rectangle.
     *
     * @param color the color to set (in web format, e.g., "#RRGGBB")
     */
    @Override
    public void setColor(String color) {
        setFill(javafx.scene.paint.Color.web(color));
    }

    /**
     * Sets the outline properties of the rectangle.
     *
     * @param width the width of the outline
     * @param color the color of the outline (in web format, e.g., "#RRGGBB")
     */
    @Override
    public void setOutline(double width, String color) {
        setStrokeWidth(width);
        setStroke(javafx.scene.paint.Color.web(color));
    }

    /**
     * Custom serialization method to write the object to an ObjectOutputStream.
     *
     * @param s the ObjectOutputStream to write to
     * @throws IOException if an I/O error occurs
     */
    private void writeObject(ObjectOutputStream s) throws IOException {
        s.defaultWriteObject();
        s.writeDouble(getX());
        s.writeDouble(getY());
        s.writeDouble(getWidth());
        s.writeDouble(getHeight());
        s.writeDouble(getRotate());
        s.writeDouble(getScaleX());
        s.writeDouble(((Color) getFill()).getRed());
        s.writeDouble(((Color) getFill()).getGreen());
        s.writeDouble(((Color) getFill()).getBlue());
    }

    /**
     * Custom deserialization method to read the object from an ObjectInputStream.
     *
     * @param s the ObjectInputStream to read from
     * @throws IOException            if an I/O error occurs
     * @throws ClassNotFoundException if the class of a serialized object cannot be found
     */
    private void readObject(ObjectInputStream s) throws IOException, ClassNotFoundException {
        double x = s.readDouble();
        double y = s.readDouble();
        double width = s.readDouble();
        double height = s.readDouble();
        double rotate = s.readDouble();
        double scale = s.readDouble();
        double red = s.readDouble();
        double green = s.readDouble();
        double blue = s.readDouble();

        setX(x);
        setY(y);
        setWidth(width);
        setHeight(height);
        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
        setFill(new Color(red, green, blue, 1));
    }
}
