package app.generator;

import app.model.IFigure;
import app.model.MyCircle;

public class CircleGenerator implements ShapeGenerator {

    
    /** 
     * @return String
     */
    @Override
    public String getShapeType() {
        return "Circle";
    }

    @Override
    public boolean isReady() {
        return points.size() > 1;
    }

    @Override
    public IFigure createShape() {
        return new MyCircle(points.get(0).getX(),
                points.get(0).getY(),
                points.get(0).distance(points.get(1)));
    }

}
