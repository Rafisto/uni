import java.util.Arrays;

import javafx.scene.control.ScrollPane;
import javafx.scene.layout.VBox;

public class GUIResultPane extends ScrollPane {

    public GUIResultPane() {
        super();
        setStyle();
    }

    public void generateResult(int size) {
        VBox result = new VBox();
        result.setAlignment(javafx.geometry.Pos.CENTER);
        for (int i = 0; i < size; i++) {
            result.getChildren().add(new GUICenteredLabel(Binomials.generateRow(i).toString().replace(",", "")));
        }
        setContent(result);
        setHvalue(0.5);
    }
    
    private void setStyle() {
        setFitToWidth(true);
        setPrefWidth(600.0);
        setStyle("-fx-background: #121212; -fx-border-color: #00aaff;");
    }
}