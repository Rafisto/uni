package app.model;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import javafx.scene.paint.Color;

/**
 * Represents a triangle shape that implements the IFigure interface.
 */
public class MyTriangle extends javafx.scene.shape.Polygon implements IFigure {

    /**
     * Constructs a MyTriangle object with the specified coordinates.
     *
     * @param x1 the x-coordinate of the first point
     * @param x2 the x-coordinate of the second point
     * @param x3 the x-coordinate of the third point
     * @param y1 the y-coordinate of the first point
     * @param y2 the y-coordinate of the second point
     * @param y3 the y-coordinate of the third point
     */
    public MyTriangle(double x1, double x2, double x3, double y1, double y2, double y3) {
        super(x1, y1, x2, y2, x3, y3);
    }

    /**
     * Scales the triangle by the specified factor.
     *
     * @param scaleFactor the scaling factor
     */
    @Override
    public void scale(double scaleFactor) {
        setScaleX(getScaleX() * scaleFactor);
        setScaleY(getScaleY() * scaleFactor);
    }

    /**
     * Moves the triangle by the specified deltas.
     *
     * @param deltaX the change in x-coordinate
     * @param deltaY the change in y-coordinate
     */
    @Override
    public void move(double deltaX, double deltaY) {
        setTranslateX(getTranslateX() + deltaX);
        setTranslateY(getTranslateY() + deltaY);
    }

    /**
     * Rotates the triangle by the specified angle.
     *
     * @param angle the rotation angle in degrees
     */
    @Override
    public void rotate(double angle) {
        setRotate(getRotate() + angle);
    }

    /**
     * Sets the fill color of the triangle.
     *
     * @param color the color to set
     */
    @Override
    public void setColor(String color) {
        setFill(javafx.scene.paint.Color.web(color));
    }

    /**
     * Sets the outline of the triangle with the specified width and color.
     *
     * @param width the width of the outline
     * @param color the color of the outline
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
        for (int i = 0; i < 6; i++) {
            s.writeDouble(getPoints().get(i));
        }
        s.writeDouble(getTranslateX());
        s.writeDouble(getTranslateY());
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
        for (int i = 0; i < 6; i++) {
            getPoints().add(s.readDouble());
        }
        double translateX = s.readDouble();
        double translateY = s.readDouble();
        double rotate = s.readDouble();
        double scale = s.readDouble();
        double red = s.readDouble();
        double green = s.readDouble();
        double blue = s.readDouble();

        setTranslateX(translateX);
        setTranslateY(translateY);
        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
        setFill(new Color(red, green, blue, 1));
    }
}
