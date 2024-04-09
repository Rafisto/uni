public class Pentagon implements Figure {
    private double side;

    public Pentagon(double s) throws IllegalArgumentException {
        if (s <= 0) {
            throw new IllegalArgumentException("Side length must be positive.");
        }
        this.side = s;
    }

    @Override
    public double area() {
        return (5 * side * side) / (4 * Math.tan(Math.PI / 5));
    }

    @Override
    public double perimeter() {
        return 5 * side;
    }

    @Override
    public String name() {
        return "Pentagon";
    }
}
