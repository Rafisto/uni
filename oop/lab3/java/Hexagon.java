public class Hexagon implements Figure {
    private double side;

    public Hexagon(double s) throws IllegalArgumentException {
        if (s <= 0) {
            throw new IllegalArgumentException("Side length must be positive.");
        }
        this.side = s;
    }

    @Override
    public double area() {
        return (3 * Math.sqrt(3) * side * side) / 2;
    }

    @Override
    public double perimeter() {
        return 6 * side;
    }

    @Override
    public String name() {
        return "Hexagon";
    }
}
