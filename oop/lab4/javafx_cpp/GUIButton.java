import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;

public class GUIButton extends Button {

    public GUIButton(String text, GUIField inputField, GUIResultPane scrollPane, GUIEventHandler handler) {
        super(text);
        setStyle();
        setOnClickEvent(inputField, scrollPane, handler);
    }

    private void setStyle() {
        AnchorPane.setRightAnchor(this, 3.0);
        setAlignment(javafx.geometry.Pos.CENTER);
        setLayoutX(228.0);
        setLayoutY(4.0);
        setMnemonicParsing(false);
        setPrefHeight(30.0);
        setPrefWidth(67.0);
        setStyle("-fx-background-color: #242424; -fx-border-width: 1; -fx-border-color: #00aaff;");
        setTextFill(javafx.scene.paint.Color.WHITE);
        setCursor(javafx.scene.Cursor.OPEN_HAND);
    }

    private void setOnClickEvent(GUIField inputField, GUIResultPane scrollPane, GUIEventHandler handler) {
        setOnAction(event -> {
            try {
                int size = Integer.parseInt(inputField.getText());
                if(size < 1 || size > 34) {
                    throw new IllegalArgumentException("Size has to be between 1 and 34, got " + size);
                }
                scrollPane.generateResult(size);
            }
            catch (IllegalArgumentException e) {
                handler.ErrorPopup(e.getMessage());
            }
          
        });
    }
}