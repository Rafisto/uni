package app.model;

/**
 * The IFigureGUI interface represents a graphical user interface for a figure.
 * It provides methods to set the color and outline of the figure, as well as
 * methods to set the figure as selected or unselected.
 */
public interface IFigureGUI {
    /**
     * Sets the color of the figure.
     *
     * @param color the color to set
     */
    void setColor(String color);

    /**
     * Sets the outline of the figure.
     *
     * @param width the width of the outline
     * @param color the color of the outline
     */
    void setOutline(double width, String color);

    /**
     * Sets the figure as selected.
     * This method sets the outline width to 2 and the outline color to "#FF00FF".
     */
    public default void setSelected() {
        setOutline(2, "#FF00FF");
    }

    /**
     * Sets the figure as unselected.
     * This method sets the outline width to 0 and the outline color to "#000000".
     */
    public default void setUnselected() {
        setOutline(0, "#000000");
    }
}
