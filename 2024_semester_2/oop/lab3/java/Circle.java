import java.lang.Math;

public class Circle extends Figure {
    private double radius;

    public Circle(double radius) throws IllegalArgumentException {
        if (radius <= 0) {
            throw new IllegalArgumentException("Radius must be positive.");
        }
        this.radius = radius;
    }

    @Override
    public double area() {
        return Math.PI * radius * radius;
    }

    @Override
    public double perimeter() {
        return 2 * Math.PI * radius;
    }

    @Override
    public String name() {
        return "Circle";
    }
}
