package app.generator;

import app.model.IFigure;
import app.model.MyRectangle;

public class RectangleGenerator implements ShapeGenerator {

    
    /** 
     * @return String
     */
    @Override
    public String getShapeType() {
        return "Rectangle";
    }

    @Override
    public boolean isReady() {
        return points.size() > 1;
    }

    @Override
    public IFigure createShape() {
        return new MyRectangle(points.get(0).getX(),
                points.get(0).getY(),
                points.get(1).getX(),
                points.get(1).getY());
    }

}
