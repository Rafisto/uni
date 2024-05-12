package app.controller;

import java.util.ArrayList;

import app.logger.AppLogger;
import javafx.scene.effect.Light.Point;

public class Drawer {
    private ArrayList<Point> points; 
    
    public Drawer() {
        points = new ArrayList<>();
    }

    public void addPoint(double x, double y) {
        AppLogger.logger.info("Point added: " + x + ", " + y);
        Point point = new Point();
        point.setX(x);
        point.setY(y);
        points.add(point);
    }

    public void drawShape() {
        AppLogger.logger.info("Drawing shape");
    }
}
