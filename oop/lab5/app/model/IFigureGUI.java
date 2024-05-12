package app.model;

public interface IFigureGUI {
    void setColor(String color);
    void setOutline(double width, String color);

    public default void setSelected() {
        setOutline(2, "#FF00FF");
    }
    public default void setUnselected() {
        setOutline(0, "#000000");
    }
}
