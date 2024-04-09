public class Rectangle extends Quadrilateral {
    private double length;
    private double width;

    public Rectangle(double l, double w) throws IllegalArgumentException {
        if (l <= 0 || w <= 0) {
            throw new IllegalArgumentException("Length and width must be positive.");
        }
        this.length = l;
        this.width = w;
    }

    @Override
    public double area() {
        return length * width;
    }

    @Override
    public double perimeter() {
        return 2 * (length + width);
    }

    @Override
    public String name() {
        return "Rectangle";
    }
}