package app.model;

public class Circle extends javafx.scene.shape.Circle implements IFigure, IFigureGUI {
    public Circle(double centerX, double centerY, double radius) {
        super(centerX, centerY, radius);
    }

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
    public void setOutline(double width) {
        setStrokeWidth(width);
    }
}
