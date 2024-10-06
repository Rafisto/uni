package app.controller;

import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.geometry.Point2D;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.layout.AnchorPane;

import app.controller.GUIMode.Mode;
import app.controller.mouse.GUIHandleDrag;
import app.controller.mouse.GUIHandleLPM;
import app.controller.mouse.GUIHandleMouseMoved;
import app.controller.mouse.GUIHandleRPM;
import app.controller.mouse.GUIHandleScroll;
import app.controller.mouse.GUIMousePosition;
import app.generator.CircleGenerator;
import app.generator.RectangleGenerator;
import app.generator.ShapeGenerator;
import app.generator.TriangleGenerator;
import app.io.PaneSerializer;
import app.logger.AppLogger;
import app.view.INFO;

/**
 * The GUIController class is responsible for handling user interactions and managing the GUI state.
 */
public final class GUIController {
    private GUIMode appState;
    private ShapeGenerator generator;
    private GUISelect selectHandler;
    private GUIColorPicker guiColorPicker;
    private GUIMousePosition initialMousePos;

    /**
     * Constructs a new GUIController object.
     */
    public GUIController() {
        this.appState = new GUIMode(this);
        this.selectHandler = new GUISelect();
        this.guiColorPicker = new GUIColorPicker();
        this.initialMousePos = new GUIMousePosition(new Point2D(0, 0));
    }

    @FXML
    private MenuItem btn_clearfile;

    /**
     * Event handler for the Clear File button.
     */
    @FXML
    public void btnClearFilePressed() {
        AppLogger.logger.info("Clear File button pressed");
        draw_pane.getChildren().clear();
    }


    @FXML
    private MenuItem btn_openfile;

    /**
     * Event handler for the Open File button.
     */
    @FXML
    public void btnOpenFilePressed() {
        AppLogger.logger.info("Open File button pressed");
        if (draw_pane == null) {
            AppLogger.logger.warning("draw_pane is null");
        }
        draw_pane.getChildren().clear();
        ObservableList<Node> deserializedNodes = PaneSerializer.deserializePane("save.file");

        draw_pane.getChildren().addAll(deserializedNodes);
    }

    @FXML
    private MenuItem btn_save;

    /**
     * Event handler for the Save button.
     */
    @FXML
    public void btnSavePressed() {
        AppLogger.logger.info("Save File button pressed");
        PaneSerializer.serializePane(draw_pane.getChildren(), "save.file");
    }

    @FXML
    private MenuItem btn_quit;

    /**
     * Event handler for the Quit button.
     */
    @FXML
    public void btnQuitPressed() {
        System.exit(0);
    }

    @FXML
    private MenuItem btn_draw_circle;

    /**
     * Event handler for the Draw Circle button.
     */
    @FXML
    public void btnDrawCirclePressed() {
        AppLogger.logger.info("Draw Circle button pressed");
        generator = new CircleGenerator();
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_draw_rectangle;

    /**
     * Event handler for the Draw Rectangle button.
     */
    @FXML
    public void btnDrawRectanglePressed() {
        AppLogger.logger.info("Draw Rectangle button pressed");
        generator = new RectangleGenerator();
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_draw_triangle;

    /**
     * Event handler for the Draw Triangle button.
     */
    @FXML
    public void btnDrawTrianglePressed() {
        AppLogger.logger.info("Draw Triangle button pressed");
        generator = new TriangleGenerator();
        appState.switchMode(Mode.DRAW);
    }

    @FXML
    private MenuItem btn_info;

    /**
     * Event handler for the Info button.
     */
    @FXML
    public void btnInfoPressed() {
        INFO.showInstructionPopup();
        AppLogger.logger.info("Info button pressed");
    }

    /**
     * Initializes the GUIController.
     */
    @FXML
    public void initialize() {
        AppLogger.logger.info("Initializing GUI Controller...");
    }

    @FXML
    private AnchorPane draw_pane;

    /**
     * Event handler for when the draw pane is pressed.
     * 
     * @param e The MouseEvent representing the press event.
     */
    @FXML
    public void drawPanePressed(MouseEvent e) {
        AppLogger.logger.info("Pressed: " + e.getButton().toString());
        if (e.getButton() == MouseButton.PRIMARY) {
            AppLogger.logger.info("Draw Pane LPM pressed at " + e.getX() + ", " + e.getY());
            GUIHandleLPM.handleLPM(e, this.appState, this.generator, this.draw_pane, this.selectHandler, this.guiColorPicker, this.initialMousePos);
        }
        else if (e.getButton() == MouseButton.SECONDARY) {
            AppLogger.logger.info("Draw Pane RPM pressed at " + e.getX() + ", " + e.getY());
            GUIHandleRPM.handleRPM(e, this.appState, this.generator, this.draw_pane, this.selectHandler, this.guiColorPicker);
        }
    }

    /**
     * Event handler for when the draw pane is dragged.
     * 
     * @param e The MouseEvent representing the drag event.
     */
    @FXML 
    public void handlePaneMouseDrag(MouseEvent e) {
        AppLogger.logger.fine("Draw Pane dragged at " + e.getX() + ", " + e.getY());
        GUIHandleDrag.handleMouseDrag(e, this.appState, this.draw_pane, this.selectHandler, this.initialMousePos);
    }

    /**
     * Event handler for when the draw pane is scrolled.
     * 
     * @param event The ScrollEvent representing the scroll event.
     */
    @FXML
    public void handlePaneScroll(ScrollEvent event) {
        AppLogger.logger.fine("Scroll event: " + event.getDeltaY());
        GUIHandleScroll.handleScroll(event, this.appState, this.draw_pane, this.selectHandler);
    }

    @FXML
    private Label label_mode;

    /**
     * Updates the mode label with the current GUI mode.
     */
    public void updateModeLabel() {
        label_mode.setText("Mode: " + appState.getCurrentMode().toString());
    }

    /**
     * Handles the event when the mouse is moved.
     *
     * @param e the MouseEvent representing the mouse movement
     */
    @FXML
    public void handleMouseMoved(MouseEvent e) {
        AppLogger.logger.fine("Mouse moved at " + e.getX() + ", " + e.getY());
        GUIHandleMouseMoved.handleMouseMoved(e, appState, draw_pane, generator);
    }
}
