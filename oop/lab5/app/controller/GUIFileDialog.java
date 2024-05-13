package app.controller;

import java.io.File;

import javafx.stage.FileChooser;
import javafx.stage.Window;

public class GUIFileDialog {
    
    /** 
     * @return File
     */
    public static File openFile() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Open File");
        return fileChooser.showOpenDialog(null);
    }

    public static File saveFile(Window window) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Save As");
        return fileChooser.showSaveDialog(window);
    }
}
