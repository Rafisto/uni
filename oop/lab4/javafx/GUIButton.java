import javafx.scene.control.Button;

public class GUIButton extends Button {

    public GUIButton(String text, GUIField inputField, GUIResultPane scrollPane) {
        super(text);
        setStyle();
        setOnClickEvent(inputField, scrollPane);
    }

    private void setStyle() {
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


    private void setOnClickEvent(GUIField inputField, GUIResultPane scrollPane) {
        setOnAction(event -> HandleClick(inputField, scrollPane));
    }

    private void HandleClick(GUIField inputField, GUIResultPane scrollPane) {
        int size = Integer.parseInt(inputField.getText());
        scrollPane.generateResult(size);
    }
}