import java.util.Arrays;

/*
 * FigureUtils
 * 
 * A static class to check validate the provided figure parameters and specific figure constraints 
 */
public final class FigureUtils {
    private static final double TOLERANCE = 1e-4;

    private FigureUtils() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    /*
     * A Square must have all sides of equal length and an angle of 90 degress.
     */
    public static boolean isSquare(double a, double b, double c, double d, double angle) {
        return Math.abs(a - b) < TOLERANCE && Math.abs(b - c) < TOLERANCE && Math.abs(c - d) < TOLERANCE
                && Math.abs(d - a) < TOLERANCE && Math.abs(angle - 90) < TOLERANCE;
    }

    /*
     * A Rhombus must have all sides of equal length and an angle between 0 and 180 degrees.
     */
    public static boolean isRhombus(double a, double b, double c, double d, double angle) {
        return Math.abs(a - b) < TOLERANCE && Math.abs(b - c) < TOLERANCE && Math.abs(c - d) < TOLERANCE
                && Math.abs(d - a) < TOLERANCE && 0 < angle && angle < 180;
    }

    /*
     * A rectangle must have two pairs of equal length sides and an angle of 90 degrees.
     */
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

    public static void printFigureInfo(String name, double area, double perimeter) {
        System.out.println("Figure name: " + name);
        System.out.println("Area: " + area);
        System.out.println("Perimeter: " + perimeter);
    }
}
