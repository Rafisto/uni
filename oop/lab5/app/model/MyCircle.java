package app.model;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import javafx.scene.paint.Color;

/**
 * Represents a custom circle shape that implements the IFigure interface.
 */
public class MyCircle extends javafx.scene.shape.Circle implements IFigure {

    /**
     * Constructs a new MyCircle object with the specified center coordinates and radius.
     *
     * @param centerX the x-coordinate of the center of the circle
     * @param centerY the y-coordinate of the center of the circle
     * @param radius  the radius of the circle
     */
    public MyCircle(double centerX, double centerY, double radius) {
        super(centerX, centerY, radius);
    }

    /**
     * Scales the circle by the specified factor.
     *
     * @param scaleFactor the factor by which to scale the circle
     */
    @Override
    public void scale(double scaleFactor) {
        setRadius(getRadius() * scaleFactor);
    }

    /**
     * Moves the circle by the specified delta values.
     *
     * @param deltaX the amount to move the circle along the x-axis
     * @param deltaY the amount to move the circle along the y-axis
     */
    @Override
    public void move(double deltaX, double deltaY) {
        setCenterX(getCenterX() + deltaX);
        setCenterY(getCenterY() + deltaY);
    }

    /**
     * Rotates the circle by the specified angle.
     *
     * @param angle the angle by which to rotate the circle
     */
    @Override
    public void rotate(double angle) {
        setRotate(getRotate() + angle);
    }

    /**
     * Sets the fill color of the circle.
     *
     * @param color the color to set as the fill color
     */
    @Override
    public void setColor(String color) {
        setFill(javafx.scene.paint.Color.web(color));
    }

    /**
     * Sets the outline color and width of the circle.
     *
     * @param width the width of the outline
     * @param color the color to set as the outline color
     */
    @Override
    public void setOutline(double width, String color) {
        setStrokeWidth(width);
        setStroke(javafx.scene.paint.Color.web(color));
    }

    /**
     * Custom serialization method to write the object to an ObjectOutputStream.
     *
     * @param s the ObjectOutputStream to write the object to
     * @throws IOException if an I/O error occurs while writing the object
     */
    private void writeObject(ObjectOutputStream s) throws IOException {
        s.defaultWriteObject();
        s.writeDouble(getCenterX());
        s.writeDouble(getCenterY());
        s.writeDouble(getRadius());
        s.writeDouble(getRotate());
        s.writeDouble(getScaleX());
        s.writeDouble(((Color) getFill()).getRed());
        s.writeDouble(((Color) getFill()).getGreen());
        s.writeDouble(((Color) getFill()).getBlue());
    }

    /**
     * Custom deserialization method to read the object from an ObjectInputStream.
     *
     * @param s the ObjectInputStream to read the object from
     * @throws IOException            if an I/O error occurs while reading the object
     * @throws ClassNotFoundException if the class of the serialized object cannot be found
     */
    private void readObject(ObjectInputStream s) throws IOException, ClassNotFoundException {
        double x = s.readDouble();
        double y = s.readDouble();
        double radius = s.readDouble();
        double rotate = s.readDouble();
        double scale = s.readDouble();
        double red = s.readDouble();
        double green = s.readDouble();
        double blue = s.readDouble();

        setCenterX(x);
        setCenterY(y);
        setRadius(radius);
        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
        setFill(new Color(red, green, blue, 1));
    }
}
