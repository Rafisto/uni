public class TestFigures {
    private TestFigures() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    private static void testFiguresNormalCase() {
        try {
            assert Figures.SingleParameterFigureEnum.CIRCLE.area(3) == Math.PI * 3 * 3;
            assert Figures.SingleParameterFigureEnum.CIRCLE.perimeter(3) == 2 * Math.PI * 3;
            assert Figures.SingleParameterFigureEnum.CIRCLE.name().equals("Circle");
            assert Figures.SingleParameterFigureEnum.PENTAGON.area(1) == (5 * 1 * 1) / (4 * Math.tan(Math.PI / 5));
            assert Figures.SingleParameterFigureEnum.PENTAGON.perimeter(1) == 5;
            assert Figures.SingleParameterFigureEnum.PENTAGON.name().equals("Pentagon");
            assert Figures.SingleParameterFigureEnum.PENTAGON.area(5.5) == (5 * 5.5 * 5.5) / (4 * Math.tan(Math.PI / 5));
            assert Figures.SingleParameterFigureEnum.PENTAGON.perimeter(5.5) == 5;
            assert Figures.SingleParameterFigureEnum.PENTAGON.name().equals("Pentagon");
            assert Figures.SingleParameterFigureEnum.HEXAGON.area(1) == (6 * 1 * 1) / (4 * Math.tan(Math.PI / 6));
            assert Figures.SingleParameterFigureEnum.HEXAGON.perimeter(1) == 6;
            assert Figures.SingleParameterFigureEnum.HEXAGON.name().equals("Hexagon");
            assert Figures.SingleParameterFigureEnum.HEXAGON.area(5.5) == (6 * 5.5 * 5.5) / (4 * Math.tan(Math.PI / 6));
            assert Figures.SingleParameterFigureEnum.HEXAGON.perimeter(5.5) == 6;
            assert Figures.SingleParameterFigureEnum.HEXAGON.name().equals("Hexagon");
            assert Figures.SingleParameterFigureEnum.SQUARE.area(1) == 1;
            assert Figures.SingleParameterFigureEnum.SQUARE.perimeter(1) == 4;
            assert Figures.SingleParameterFigureEnum.SQUARE.name().equals("Square");
            assert Figures.SingleParameterFigureEnum.SQUARE.area(5.5) == 5.5 * 5.5;
            assert Figures.SingleParameterFigureEnum.SQUARE.perimeter(5.5) == 4 * 5.5;
            assert Figures.SingleParameterFigureEnum.SQUARE.name().equals("Square");
            assert Figures.TwoParameterFigureEnum.RECTANGLE.area(1, 1) == 1;
            assert Figures.TwoParameterFigureEnum.RECTANGLE.perimeter(1, 1) == 4;
            assert Figures.TwoParameterFigureEnum.RECTANGLE.name().equals("Rectangle");
            assert Figures.TwoParameterFigureEnum.RECTANGLE.area(5.5, 5.5) == 5.5 * 5.5;
            assert Figures.TwoParameterFigureEnum.RECTANGLE.perimeter(5.5, 5.5) == 4 * 5.5;
            assert Figures.TwoParameterFigureEnum.RECTANGLE.name().equals("Rectangle");
            assert Figures.TwoParameterFigureEnum.RHOMBUS.area(1, 30) == 0.5;
            assert Figures.TwoParameterFigureEnum.RHOMBUS.perimeter(1, 30) == 4;
            assert Figures.TwoParameterFigureEnum.RHOMBUS.name().equals("Rhombus");
            assert Figures.TwoParameterFigureEnum.RHOMBUS.area(5.5, 30) == 0.5 * 5.5 * 5.5;
            assert Figures.TwoParameterFigureEnum.RHOMBUS.perimeter(5.5, 30) == 4 * 5.5;
            assert Figures.TwoParameterFigureEnum.RHOMBUS.name().equals("Rhombus");
            assert Figures.TwoParameterFigureEnum.RHOMBUS.area(5.5, 60) == 5.5 * 5.5 * Math.sin(Math.toRadians(60));
            assert Figures.TwoParameterFigureEnum.RHOMBUS.perimeter(5.5, 60) == 4 * 5.5;
            assert Figures.TwoParameterFigureEnum.RHOMBUS.name().equals("Rhombus");
        } catch (IllegalArgumentException e) {
            System.out.println("Exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void testFiguresExceptions() {

    }

    public static void testFigures() {
        testFiguresNormalCase();
        testFiguresExceptions();
    }
}
