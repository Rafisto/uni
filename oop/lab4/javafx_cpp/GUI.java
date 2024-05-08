import javafx.scene.Scene;
import javafx.stage.Stage;

public class GUI {
    public GUI(Stage primaryStage) {
        AppLogger.logger.info("Loading GUIEventHandler");
        GUIEventHandler handler = new GUIEventHandler(primaryStage);
        GUISkeleton gui = new GUISkeleton();
        
        GUILabel label = new GUILabel("Type in the number of rows (1-34)");
        GUIField sizeField = new GUIField("0");
        GUIResultPane resultPane = new GUIResultPane();
        GUIButton displayButton = new GUIButton("Display", sizeField, resultPane, handler);

        gui.getTopGridPane().add(label, 0, 0);      
        gui.getAnchorPane().getChildren().add(sizeField);
        gui.getAnchorPane().getChildren().add(displayButton);
        gui.getRoot().setCenter(resultPane);

        Scene scene = new Scene(gui.getRoot());
        primaryStage.setScene(scene);
        primaryStage.setTitle("JavaFX Pascal Triangle");
        primaryStage.show();
        AppLogger.logger.info("Rendered the scene");
    }
}