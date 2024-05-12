package app.controller;

import javafx.fxml.FXML;
import javafx.scene.control.MenuItem;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;

import app.controller.GUIState.Mode;
import app.logger.AppLogger;

public class GUIController {
    private GUIState appState;
    private Drawer drawer;
    private GUIClickHandler clickHandler;

    public GUIController() {
        this.appState = new GUIState();
        this.drawer = new Drawer(draw_pane);
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
        drawer.setShape(DrawerShape.CIRCLE);
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_draw_rectangle;

    @FXML
    public void btnDrawRectanglePressed() {
        AppLogger.logger.info("Draw Rectangle button pressed");
        drawer.setShape(DrawerShape.RECTANGLE);
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_draw_triangle;

    @FXML
    public void btnDrawTrianglePressed() {
        AppLogger.logger.info("Draw Triangle button pressed");
        drawer.setShape(DrawerShape.TRIANGLE);
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

    @FXML
    public void drawPanePressed(MouseEvent e) {
        AppLogger.logger.info("Draw Pane pressed at " + e.getX() + ", " + e.getY());
        clickHandler.handleLPM(e, appState, drawer, draw_pane);
    }
}
