package app.controller;

import java.util.ArrayList;

import app.logger.AppLogger;
import app.model.MyCircle;
import app.model.MyRectangle;
import app.model.MyTriangle;
import javafx.geometry.Point2D;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Shape;

public class Drawer {
    private ArrayList<Point2D> points;
    private DrawerShape drawer_shape;
    private GUISelect selectHandler;

    public Drawer(Pane draw_pane, GUISelect selectHandler) {
        this.selectHandler = selectHandler;
        points = new ArrayList<>();
    }

    public void setShape(DrawerShape shape) {
        AppLogger.logger.info("Setting shape: " + shape);
        this.drawer_shape = shape;
        this.points.clear();
    }

    public boolean isReady() {
        if (this.points == null) {
            return false;
        }

        switch (this.drawer_shape) {
            case CIRCLE:
                return this.points.size() == 2;
            case RECTANGLE:
                return this.points.size() == 2;
            case TRIANGLE:
                return this.points.size() == 3;
            default:
                return false;
        }
    }

    public void addPoint(double x, double y) {
        points.add(new Point2D(x, y));
        AppLogger.logger.info("Point added: " + x + ", " + y);
        AppLogger.logger.info("Points count: " + points.size());
    }

    public void drawShape(Pane draw_pane) {
        AppLogger.logger.info("Drawing shape");
        if (!this.isReady()) {
            AppLogger.logger.warning("Shape is not ready");
            return;
        }
        Shape s;
        switch (this.drawer_shape) {
            case CIRCLE:
                s = new MyCircle(this.points.get(0).getX(),
                        this.points.get(0).getY(),
                        this.points.get(0).distance(this.points.get(1)));
                break;
            case RECTANGLE:
                s = new MyRectangle(this.points.get(0).getX(),
                        this.points.get(0).getY(),
                        this.points.get(1).getX(),
                        this.points.get(1).getY());
                break;
            case TRIANGLE:
                s = new MyTriangle(this.points.get(0).getX(),
                        this.points.get(1).getX(),
                        this.points.get(2).getX(),
                        this.points.get(0).getY(),
                        this.points.get(1).getY(),
                        this.points.get(2).getY());
                break;
            default:
                AppLogger.logger.warning("Unknown shape");
                return;
        }
        this.points.clear();
        selectHandler.UnselectAll(draw_pane);
        draw_pane.getChildren().add(s);
    }
}
