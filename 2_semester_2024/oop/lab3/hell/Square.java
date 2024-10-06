public class Square extends Quadrilateral {
    private double side;

    public Square(double s) throws IllegalArgumentException {
        if (s <= 0) {
            throw new IllegalArgumentException("Side length must be positive.");
        }
        this.side = s;
    }

    @Override
    public double area() {
        return side * side;
    }

    @Override
    public double perimeter() {
        return 4 * side;
    }

    @Override
    public String name() {
        return "Square";
    }
}