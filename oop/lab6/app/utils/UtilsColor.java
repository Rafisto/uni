package app.utils;

import java.util.ArrayList;

import javafx.scene.paint.Color;

public final class UtilsColor {

    /**
     * Creates a random color.
     *
     * @return a randomly generated color.
     */
    public static final Color randomColor() {
        return Color.rgb((int) (Math.random() * 256), (int) (Math.random() * 256), (int) (Math.random() * 256));
    }

    /**
     * Calculates the average color from a list of colors.
     *
     * @param colors The list of colors to calculate the average from.
     * @return The average color.
     */
    public static final Color calculateNewColor(ArrayList<Color> colors) {
        if (colors.size() == 0) {
            return randomColor();
        }

        double red = 0;
        double green = 0;
        double blue = 0;

        for (Color color : colors) {
            red += color.getRed();
            green += color.getGreen();
            blue += color.getBlue();
        }

        return Color.color(red / colors.size(), green / colors.size(), blue / colors.size());
    }
}
