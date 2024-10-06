package app.controller;


public class GUIEventHandler {
    /**
     * The `GUIEventHandler` class is a utility class that handles events in the GUI.
     * It provides static methods for handling various events in the application's graphical user interface.
     * This class cannot be instantiated as it only contains static methods.
     */
    private GUIEventHandler() throws IllegalStateException {
        throw new IllegalStateException("Utility class");
    }
    /**
     * Displays an error popup with the given text.
     *
     * @param text the text to be displayed in the error popup
     */
    public static void ErrorPopup(String text) {
        new GUIPopup(null, text);
    }
}