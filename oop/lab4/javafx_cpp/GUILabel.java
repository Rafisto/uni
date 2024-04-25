import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;

public class GUILabel extends Label {

    public GUILabel(String text) {
        super(text);
        setStyle();
    }

    private void setStyle() {
        GridPane.setHalignment(this, javafx.geometry.HPos.CENTER);
        setAlignment(javafx.geometry.Pos.TOP_LEFT);
        setTextAlignment(javafx.scene.text.TextAlignment.CENTER);
        setTextFill(javafx.scene.paint.Color.WHITE);
    }
}