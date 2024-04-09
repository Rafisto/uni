import java.util.Arrays;

public class FigureUtils {
    private static final double TOLERANCE = 1e-4;

    private FigureUtils() {
    }

    public static boolean isSquare(double a, double b, double c, double d, double angle) {
        return Math.abs(a - b) < TOLERANCE && Math.abs(b - c) < TOLERANCE && Math.abs(c - d) < TOLERANCE
                && Math.abs(d - a) < TOLERANCE && Math.abs(angle - 90) < TOLERANCE;
    }

    public static boolean isRhombus(double a, double b, double c, double d) {
        return Math.abs(a - b) < TOLERANCE && Math.abs(b - c) < TOLERANCE && Math.abs(c - d) < TOLERANCE
                && Math.abs(d - a) < TOLERANCE;
    }

    public static boolean isRectangle(double a, double b, double c, double d, double angle) {
        if (Math.abs(angle - 90) > TOLERANCE)
            return false;

        double[] sides = { a, b, c, d };
        Arrays.sort(sides);

        return (Math.abs(sides[0] - sides[1]) < TOLERANCE &&
                Math.abs(sides[2] - sides[3]) < TOLERANCE &&
                Math.abs(sides[1] - sides[2]) > TOLERANCE);
    }

    public static void printFigureInfo(Figure figure) {
        System.out.println("Figure name: " + figure.name());
        System.out.println("Area: " + figure.area());
        System.out.println("Perimeter: " + figure.perimeter());
    }
}
