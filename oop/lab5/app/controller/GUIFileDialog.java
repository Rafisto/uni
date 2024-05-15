package app.controller;

import java.io.File;

import javafx.stage.FileChooser;
import javafx.stage.Window;

/**
 * The GUIFileDialog class provides methods for opening and saving files using a graphical user interface.
 */
public class GUIFileDialog {
    
    /** 
     * Opens a file dialog for selecting a file to open.
     * 
     * @return The selected File object, or null if no file was selected.
     */
    public static File openFile() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Open File");
        return fileChooser.showOpenDialog(null);
    }

    /**
     * Opens a file dialog for selecting a file to save.
     * 
     * @param window The parent window for the file dialog.
     * @return The selected File object, or null if no file was selected.
     */
    public static File saveFile(Window window) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Save As");
        return fileChooser.showSaveDialog(window);
    }
}
