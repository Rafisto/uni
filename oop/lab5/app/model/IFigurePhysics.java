package app.model;

public interface IFigurePhysics {
    void scale(double scaleFactor);
    void move(double deltaX, double deltaY);
    void rotate(double angle);
}