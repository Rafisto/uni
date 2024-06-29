import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;

public class GUIField extends TextField {

    public GUIField(String text) {
        super(text);
        setStyle();
    }

    private void setStyle() {
        AnchorPane.setLeftAnchor(this, 4.0);
        AnchorPane.setRightAnchor(this, 72.0);
        setAccessibleHelp("Number of rows");
        setAccessibleRoleDescription("Number of rows");
        setAccessibleText("Number of rows");
        setAlignment(javafx.geometry.Pos.CENTER);
        setLayoutX(4.0);
        setLayoutY(4.0);
        setPrefHeight(30.0);
        setPrefWidth(222.0);
        setStyle("-fx-background-color: #242424; -fx-border-color: #00aaff; -fx-border-width: 1; -fx-text-fill: #ffffff;");
    }
}