import javafx.stage.Stage;

public class GUIEventHandler {
    private Stage owner;
    public GUIEventHandler(Stage owner) {
        this.owner = owner;
    }

    public void ErrorPopup(String text) {
        new GUIPopup(owner, text);
    }
}
