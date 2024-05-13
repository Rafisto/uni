package app.model;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import javafx.scene.paint.Color;

public class MyCircle extends javafx.scene.shape.Circle implements IFigure {
    public MyCircle(double centerX, double centerY, double radius) {
        super(centerX, centerY, radius);
    }
    
    /** 
     * @param scaleFactor
     */
    @Override
    public void scale(double scaleFactor) {
        setRadius(getRadius() * scaleFactor);
    }

    @Override
    public void move(double deltaX, double deltaY) {
        setCenterX(getCenterX() + deltaX);
        setCenterY(getCenterY() + deltaY);
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
        s.writeDouble(getCenterX());
        s.writeDouble(getCenterY());
        s.writeDouble(getRadius());
        s.writeDouble(getRotate());
        s.writeDouble(getScaleX());
        s.writeDouble(((Color)getFill()).getRed());
        s.writeDouble(((Color)getFill()).getGreen());
        s.writeDouble(((Color)getFill()).getBlue());
    }
    
    private void readObject(ObjectInputStream s) throws IOException, ClassNotFoundException {
        double x = s.readDouble();
        double y = s.readDouble();
        double radius = s.readDouble();
        double rotate = s.readDouble();
        double scale  = s.readDouble();
        double red = s.readDouble();
        double green = s.readDouble();
        double blue = s.readDouble();

        setCenterX(x);
        setCenterY(y);
        setRadius(radius);
        setRotate(rotate);
        setScaleX(scale);
        setScaleY(scale);
        setFill(new Color(red,green,blue,1));
    }
}
