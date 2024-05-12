package app.model;

interface IFigure {
    void scale(double scaleFactor);
    void move(double deltaX, double deltaY);
    void rotate(double angle);
}