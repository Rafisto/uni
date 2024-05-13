package app.model;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import javafx.scene.paint.Color;

public class MyRectangle extends javafx.scene.shape.Rectangle implements IFigure {
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
     * @param scaleFactor
     */
    @Override
    public void scale(double scaleFactor) {
        setWidth(scaleFactor * getWidth());
        setHeight(scaleFactor * getHeight());
    }

    @Override
    public void move(double deltaX, double deltaY) {
        setX(getX() + deltaX);
        setY(getY() + deltaY);
    }

    @Override
    public void rotate(double angle) {
        setRotate(getRotate() + angle);
    }

    @Override
    public void setColor(String color) {
        setFill(javafx.scene.paint.Color.web(color));
    }

    @Override
    public void setOutline(double width, String color) {
        setStrokeWidth(width);
        setStroke(javafx.scene.paint.Color.web(color));
    }

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
