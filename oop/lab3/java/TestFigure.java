public class TestFigure {
    private TestFigure() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    private static void testFigureNormalCase() {
        try {
            assert new Circle(1).area() == Math.PI;
            assert new Circle(1).perimeter() == 2 * Math.PI;
            assert new Circle(1).name().equals("Circle");
            assert new Circle(10).area() == 100 * Math.PI;
            assert new Circle(10).perimeter() == 20 * Math.PI;
            assert new Circle(10).name().equals("Circle");
            assert new Pentagon(1).area() == (5 * 1 * 1) / (4 * Math.tan(Math.PI / 5));
            assert new Pentagon(1).perimeter() == 5;
            assert new Pentagon(1).name().equals("Pentagon");
            assert new Pentagon(5.5).area() == (5 * 5.5 * 5.5) / (4 * Math.tan(Math.PI / 5));
            assert new Pentagon(5.5).perimeter() == 5;
            assert new Pentagon(5.5).name().equals("Pentagon");
            assert new Hexagon(1).area() == (6 * 1 * 1) / (4 * Math.tan(Math.PI / 6));
            assert new Hexagon(1).perimeter() == 6;
            assert new Hexagon(1).name().equals("Hexagon");
            assert new Hexagon(5.5).area() == (6 * 5.5 * 5.5) / (4 * Math.tan(Math.PI / 6));
            assert new Hexagon(5.5).perimeter() == 6;
            assert new Hexagon(5.5).name().equals("Hexagon");
            assert new Square(1).area() == 1;
            assert new Square(1).perimeter() == 4;
            assert new Square(1).name().equals("Square");
            assert new Square(5.5).area() == 5.5 * 5.5;
            assert new Square(5.5).perimeter() == 4 * 5.5;
            assert new Square(5.5).name().equals("Square");
            assert new Rectangle(1, 1).area() == 1;
            assert new Rectangle(1, 1).perimeter() == 4;
            assert new Rectangle(1, 1).name().equals("Rectangle");
            assert new Rectangle(5.5, 5.5).area() == 5.5 * 5.5;
            assert new Rectangle(5.5, 5.5).perimeter() == 4 * 5.5;
            assert new Rectangle(5.5, 5.5).name().equals("Rectangle");
            assert new Rhombus(1, 30).area() == 0.5;
            assert new Rhombus(1, 30).perimeter() == 4;
            assert new Rhombus(1, 30).name().equals("Rhombus");
            assert new Rhombus(5.5, 30).area() == 0.5 * 5.5 * 5.5;
            assert new Rhombus(5.5, 30).perimeter() == 4 * 5.5;
            assert new Rhombus(5.5, 30).name().equals("Rhombus");
            assert new Rhombus(5.5, 60).area() == 5.5 * 5.5 * Math.sin(Math.toRadians(60));
            assert new Rhombus(5.5, 60).perimeter() == 4 * 5.5;
            assert new Rhombus(5.5, 60).name().equals("Rhombus");
        } catch (IllegalArgumentException e) {
            System.out.println("Exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void testFigureExceptions() {
        try {
            new Circle(-1);
            System.out.println("Test failed: No exception thrown for circle with negative radius.");
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
        try {
            new Pentagon(-1);
            System.out.println("Test failed: No exception thrown for pentagon with negative side length.");
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
        try {
            new Hexagon(-1);
            System.out.println("Test failed: No exception thrown for hexagon with negative side length.");
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
        try {
            new Square(-1);
            System.out.println("Test failed: No exception thrown for square with negative side length.");
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
        try {
            new Rectangle(-1, 1);
            System.out.println("Test failed: No exception thrown for rectangle with negative side length.");
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
        try {
            new Rhombus(-1, 1);
            System.out.println("Test failed: No exception thrown for rhombus with negative side length.");
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
        try {
            new Rhombus(1, 720);
            System.out.println("Test failed: No exception thrown for rhombus with angle greater than 360.");
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
    }

    public static void testFigure() {
        testFigureNormalCase();
        testFigureExceptions();
    }
}
