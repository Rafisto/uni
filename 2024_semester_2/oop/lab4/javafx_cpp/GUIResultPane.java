import java.util.List;

import javax.management.RuntimeErrorException;

import javafx.scene.control.ScrollPane;
import javafx.scene.layout.VBox;

public class GUIResultPane extends ScrollPane {

    public GUIResultPane() {
        super();
        setStyle();
    }

    public void generateResult(int size) {
        AppLogger.logger.info("Generating Result for size: " + size);
        VBox result = new VBox();
        result.setAlignment(javafx.geometry.Pos.CENTER);
        for (int i = 0; i < size; i++) {
            try {
                List<Integer> list = PascalRowInvoker.InvokeRow(i);
                result.getChildren().add(new GUICenteredLabel(list.toString().replace(",", "")));
            } catch (RuntimeErrorException e) {
                AppLogger.logger.warning("Unable to invoke the cpp program: "+e.getMessage());
                break;
            }
        }
        setContent(result);
        setHvalue(0.5);
        AppLogger.logger.info("Successfully generated result for size: " + size);
    }

    private void setStyle() {
        setFitToWidth(true);
        setPrefWidth(600.0);
        setStyle("-fx-background: #121212; -fx-border-color: #00aaff;");
    }
}