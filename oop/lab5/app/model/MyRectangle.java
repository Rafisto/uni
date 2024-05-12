package app.model;

public class MyRectangle extends javafx.scene.shape.Rectangle implements IFigure, IFigureGUI {
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
}
