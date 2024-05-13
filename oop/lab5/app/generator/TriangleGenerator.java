package app.generator;

import app.model.IFigure;
import app.model.MyTriangle;

public class TriangleGenerator implements ShapeGenerator {

    
    /** 
     * @return String
     */
    @Override
    public String getShapeType() {
        return "Triangle";
    }

    @Override
    public boolean isReady() {
        return points.size() > 2;
    }

    @Override
    public IFigure createShape() {
        return new MyTriangle(points.get(0).getX(),
                points.get(1).getX(),
                points.get(2).getX(),
                points.get(0).getY(),
                points.get(1).getY(),
                points.get(2).getY());
    }

}
