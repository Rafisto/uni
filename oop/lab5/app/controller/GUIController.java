package app.controller;

import app.logger.AppLogger;
import javafx.fxml.FXML;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuItem;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;

public class GUIController {
    private AppState appState;
    private Drawer drawer;
    private ClickHandler clickHandler;

    public GUIController() {
        this.appState = new AppState();
        this.drawer = new Drawer();
        this.clickHandler = new ClickHandler();
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
        appState.switchToDrawMode();
    }

    @FXML
    private MenuItem btn_draw_rectangle;

    @FXML
    public void btnDrawRectanglePressed() {
        AppLogger.logger.info("Draw Rectangle button pressed");
        appState.switchToDrawMode();
    }

    @FXML
    private MenuItem btn_draw_triangle;

    @FXML
    public void btnDrawTrianglePressed() {
        AppLogger.logger.info("Draw Triangle button pressed");
        appState.switchToDrawMode();
    }

    @FXML
    private Menu btn_info;

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

    @FXML
    public void drawPanePressed(MouseEvent e) {
        AppLogger.logger.info("Draw Pane pressed at " + e.getX() + ", " + e.getY());
        clickHandler.handleLPM(e, appState, drawer);
    }

    public AnchorPane getDrawPane() {
        return draw_pane;
    }
}
