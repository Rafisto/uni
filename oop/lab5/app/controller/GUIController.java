package app.controller;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.layout.AnchorPane;
import app.controller.GUIMode.Mode;
import app.generator.CircleGenerator;
import app.generator.RectangleGenerator;
import app.generator.ShapeGenerator;
import app.generator.TriangleGenerator;
import app.logger.AppLogger;

public class GUIController {
    private GUIMode appState;
    private ShapeGenerator generator;
    private GUIClickHandler clickHandler;
    private GUISelect selectHandler;
    private GUIColorPicker guiColorPicker;

    public GUIController() {
        this.appState = new GUIMode(this);
        this.selectHandler = new GUISelect();
        this.guiColorPicker = new GUIColorPicker(this.appState);
        this.clickHandler = new GUIClickHandler();
    }

    @FXML
    private MenuItem btn_openfile;

    @FXML
    public void btnOpenFilePressed() {
        AppLogger.logger.info("Open File button pressed");
        GUIFileDialog.openFile();
    }

    @FXML
    private MenuItem btn_save;

    @FXML
    public void btnSavePressed() {
        AppLogger.logger.info("Save button pressed");
    }

    @FXML
    private MenuItem btn_saveas;

    @FXML
    public void btnSaveAsPressed() {
        AppLogger.logger.info("Save as button pressed");
    }

    @FXML
    private MenuItem btn_quit;

    @FXML
    public void btnQuitPressed() {
        System.exit(0);
    }

    @FXML
    private MenuItem btn_draw_circle;

    @FXML
    public void btnDrawCirclePressed() {
        AppLogger.logger.info("Draw Circle button pressed");
        generator = new CircleGenerator();
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_draw_rectangle;

    @FXML
    public void btnDrawRectanglePressed() {
        AppLogger.logger.info("Draw Rectangle button pressed");
        generator = new RectangleGenerator();
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_draw_triangle;

    @FXML
    public void btnDrawTrianglePressed() {
        AppLogger.logger.info("Draw Triangle button pressed");
        generator = new TriangleGenerator();
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_info;

    @FXML
    public void btnInfoPressed() {
        AppLogger.logger.info("Info button pressed");
    }

    @FXML
    public void initialize() {
        AppLogger.logger.info("Initializing GUI Controller...");
    }

    @FXML
    private AnchorPane draw_pane;

    
    /** 
     * @param e
     */
    @FXML
    public void drawPanePressed(MouseEvent e) {
        AppLogger.logger.info("Pressed: " + e.getButton().toString());
        if (e.getButton() == MouseButton.PRIMARY) {
            AppLogger.logger.info("Draw Pane LPM pressed at " + e.getX() + ", " + e.getY());
            clickHandler.handleLPM(e, this.appState, this.generator, this.draw_pane, this.selectHandler, this.guiColorPicker);
        }
        else if (e.getButton() == MouseButton.SECONDARY) {
            AppLogger.logger.info("Draw Pane RPM pressed at " + e.getX() + ", " + e.getY());
            clickHandler.handleRPM(e, this.appState, this.generator, this.draw_pane, this.selectHandler, this.guiColorPicker);
        }
    }

    @FXML 
    public void handlePaneMouseDrag(MouseEvent e) {
        AppLogger.logger.fine("Draw Pane dragged at " + e.getX() + ", " + e.getY());
        clickHandler.handleMouseDrag(e, this.appState, this.draw_pane, this.selectHandler);
    }

    @FXML
    public void handlePaneScroll(ScrollEvent event) {
        AppLogger.logger.fine("Scroll event: " + event.getDeltaY());
        clickHandler.handleScroll(event, this.appState, this.draw_pane, this.selectHandler);
    }

    @FXML
    private Label label_mode;

    public void updateModeLabel() {
        label_mode.setText("Mode: " + appState.getCurrentMode().toString());
    }
}
