package app.model;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import javafx.scene.paint.Color;

public class MyTriangle extends javafx.scene.shape.Polygon implements IFigure {
    public MyTriangle(double x1, double x2, double x3, double y1, double y2, double y3) {
        super(x1, y1, x2, y2, x3, y3);
    }

    /**
     * @param scaleFactor
     */
    @Override
    public void scale(double scaleFactor) {
        setScaleX(getScaleX() * scaleFactor);
        setScaleY(getScaleY() * scaleFactor);
    }

    @Override
    public void move(double deltaX, double deltaY) {
        setTranslateX(getTranslateX() + deltaX);
        setTranslateY(getTranslateY() + deltaY);
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
        for (int i = 0; i < 6; i++) {
            s.writeDouble(getPoints().get(i));
        }
        s.writeDouble(getRotate());
        s.writeDouble(getScaleX());
        s.writeDouble(((Color) getFill()).getRed());
        s.writeDouble(((Color) getFill()).getGreen());
        s.writeDouble(((Color) getFill()).getBlue());
    }

    private void readObject(ObjectInputStream s) throws IOException, ClassNotFoundException {
        for (int i = 0; i < 6; i++) {
            getPoints().add(s.readDouble());
        }
        double rotate = s.readDouble();
        double scale = s.readDouble();
        double red = s.readDouble();
        double green = s.readDouble();
        double blue = s.readDouble();

        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
        setFill(new Color(red, green, blue, 1));
    }
}
