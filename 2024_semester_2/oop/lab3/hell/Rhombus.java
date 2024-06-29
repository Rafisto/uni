public class Rhombus extends Quadrilateral {
    private double side;
    private double angle;

    public Rhombus(double s, double a) throws IllegalArgumentException {
        if (s <= 0 || a <= 0 || a > 180) {
            throw new IllegalArgumentException("Side length and angle must be positive.");
        }
        this.side = s;
        this.angle = a;
    }

    @Override
    public double area() {
        return side * side * Math.sin(Math.toRadians(angle));
    }

    @Override
    public double perimeter() {
        return 4 * side;
    }

    @Override
    public String name() {
        return "Rhombus";
    }
}