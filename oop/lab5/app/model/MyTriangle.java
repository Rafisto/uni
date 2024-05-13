package app.model;

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
}
