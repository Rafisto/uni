import javafx.scene.control.Label;

public class GUICenteredLabel extends Label {

    public GUICenteredLabel(String text) {
        super(text);
        setStyle();
    }

    private void setStyle() {
        setAlignment(javafx.geometry.Pos.CENTER);
        setTextAlignment(javafx.scene.text.TextAlignment.CENTER);
        setTextFill(javafx.scene.paint.Color.WHITE);
    }
}