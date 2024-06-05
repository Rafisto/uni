package app.utils;

import java.util.ArrayList;

import javafx.scene.paint.Color;

public class UtilsColor {
    public static Color randomColor() {
        return Color.rgb((int) (Math.random() * 256), (int) (Math.random() * 256), (int) (Math.random() * 256));
    }

    public static Color calculateNewColor(ArrayList<Color> colors) {
        if (colors.size() == 0) {
            return Color.WHITE;
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
