package app.model;

/**
 * The IFigurePhysics interface represents the physics behavior of a figure.
 * It provides methods to scale, move, and rotate the figure.
 */
public interface IFigurePhysics {
    /**
     * Scales the figure by the given scaleFactor.
     *
     * @param scaleFactor the factor by which to scale the figure
     */
    void scale(double scaleFactor);

    /**
     * Moves the figure by the given deltaX and deltaY.
     *
     * @param deltaX the amount to move the figure along the x-axis
     * @param deltaY the amount to move the figure along the y-axis
     */
    void move(double deltaX, double deltaY);

    /**
     * Rotates the figure by the given angle.
     *
     * @param angle the angle by which to rotate the figure
     */
    void rotate(double angle);
}