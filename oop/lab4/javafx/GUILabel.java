import javafx.scene.control.Label;

public class GUILabel extends Label {

    public GUILabel(String text) {
        super(text);
        setStyle();
    }

    private void setStyle() {
        setAlignment(javafx.geometry.Pos.TOP_LEFT);
        setTextAlignment(javafx.scene.text.TextAlignment.CENTER);
        setTextFill(javafx.scene.paint.Color.WHITE);
    }
}