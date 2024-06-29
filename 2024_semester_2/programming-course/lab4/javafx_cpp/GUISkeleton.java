import javafx.scene.control.SplitPane;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;

public class GUISkeleton {
    private BorderPane root;
    private GridPane topGridPane;
    private AnchorPane anchorPane;
    
    public BorderPane getRoot() {
        return this.root;
    }
    
    public GridPane getTopGridPane() {
        return topGridPane;
    }
    
    public AnchorPane getAnchorPane() {
        return anchorPane;
    }

    public GUISkeleton() { 
        this.root = new BorderPane();
        this.root.setMaxHeight(Double.MAX_VALUE);
        this.root.setMaxWidth(Double.MAX_VALUE);
        this.root.setPrefHeight(400.0);
        this.root.setPrefWidth(600.0);
        this.root.setStyle("-fx-background-color: #121212;");

        this.topGridPane = new GridPane();
        this.topGridPane.setPrefHeight(40.0);
        this.topGridPane.setStyle("-fx-background-color: #121212;");
        this.root.setTop(topGridPane);

        ColumnConstraints column1 = new ColumnConstraints();
        column1.setHgrow(javafx.scene.layout.Priority.SOMETIMES);
        column1.setMinWidth(10.0);
        column1.setPrefWidth(100.0);

        ColumnConstraints column2 = new ColumnConstraints();
        column2.setHgrow(javafx.scene.layout.Priority.SOMETIMES);
        column2.setMinWidth(10.0);
        column2.setPrefWidth(100.0);

        this.topGridPane.getColumnConstraints().addAll(column1, column2);

        RowConstraints row = new RowConstraints();
        row.setMinHeight(10.0);
        row.setPrefHeight(30.0);
        row.setVgrow(javafx.scene.layout.Priority.SOMETIMES);

        this.topGridPane.getRowConstraints().add(row);
        
        SplitPane splitPane = new SplitPane();
        splitPane.setPrefHeight(160.0);
        splitPane.setPrefWidth(200.0);
        splitPane.setStyle("-fx-background-color: #121212;");
        GridPane.setColumnIndex(splitPane, 1);
        this.topGridPane.getChildren().add(splitPane);
        
        this.anchorPane = new AnchorPane();
        this.anchorPane.setPrefHeight(200.0);
        this.anchorPane.setPrefWidth(200.0);
        this.anchorPane.setStyle("-fx-background-color: #121212;");
        splitPane.getItems().add(anchorPane);
    }
}
