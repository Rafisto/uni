import javafx.scene.Scene;
import javafx.scene.control.SplitPane;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.stage.Stage;

public class GUI {
    public GUI(Stage primaryStage) {
        BorderPane root = new BorderPane();
        root.setMaxHeight(Double.MAX_VALUE);
        root.setMaxWidth(Double.MAX_VALUE);
        root.setPrefHeight(400.0);
        root.setPrefWidth(600.0);
        root.setStyle("-fx-background-color: #121212;");

        GridPane topGridPane = new GridPane();
        topGridPane.setPrefHeight(40.0);
        topGridPane.setStyle("-fx-background-color: #121212;");
        root.setTop(topGridPane);

        ColumnConstraints column1 = new ColumnConstraints();
        column1.setHgrow(javafx.scene.layout.Priority.SOMETIMES);
        column1.setMinWidth(10.0);
        column1.setPrefWidth(100.0);

        ColumnConstraints column2 = new ColumnConstraints();
        column2.setHgrow(javafx.scene.layout.Priority.SOMETIMES);
        column2.setMinWidth(10.0);
        column2.setPrefWidth(100.0);

        topGridPane.getColumnConstraints().addAll(column1, column2);

        RowConstraints row = new RowConstraints();
        row.setMinHeight(10.0);
        row.setPrefHeight(30.0);
        row.setVgrow(javafx.scene.layout.Priority.SOMETIMES);

        topGridPane.getRowConstraints().add(row);

        GUILabel label = new GUILabel("Type in the number of rows (1-33)");
        GridPane.setHalignment(label, javafx.geometry.HPos.CENTER);
        topGridPane.add(label, 0, 0);

        SplitPane splitPane = new SplitPane();
        splitPane.setPrefHeight(160.0);
        splitPane.setPrefWidth(200.0);
        splitPane.setStyle("-fx-background-color: #121212;");
        GridPane.setColumnIndex(splitPane, 1);
        topGridPane.getChildren().add(splitPane);

        AnchorPane anchorPane = new AnchorPane();
        anchorPane.setPrefHeight(200.0);
        anchorPane.setPrefWidth(200.0);
        anchorPane.setStyle("-fx-background-color: #121212;");
        splitPane.getItems().add(anchorPane);

        
        GUIField sizeField = new GUIField("0");
        AnchorPane.setLeftAnchor(sizeField, 4.0);
        AnchorPane.setRightAnchor(sizeField, 72.0);
        anchorPane.getChildren().add(sizeField);
        
        GUIResultPane resultPane = new GUIResultPane();
        root.setCenter(resultPane);
        
        GUIButton displayButton = new GUIButton("Display", sizeField, resultPane);
        AnchorPane.setRightAnchor(displayButton, 3.0);
        anchorPane.getChildren().add(displayButton);

        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}