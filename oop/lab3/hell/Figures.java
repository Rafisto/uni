/*
 * Figures class having two enums for single parameter and two parameter figure
 * ~ The Third Exercise
 */
public class Figures {
    interface SingleParameterFigure {
        double area(double a);

        double perimeter(double a);

        String name();
    }

    interface TwoParameterFigure {
        double area(double a, double b);

        double perimeter(double a, double b);

        String name();
    }

    public enum SingleParameterFigureEnum implements SingleParameterFigure {
        CIRCLE {
            @Override
            public double area(double a) {
                return new Circle(a).area();
            }

            @Override
            public double perimeter(double a) {
                return new Circle(a).perimeter();
            }

            @Override
            public String figureName() {
                return "Circle";
            }
        },
        SQUARE {
            @Override
            public double area(double a) {
                return new Square(a).area();
            }

            @Override
            public double perimeter(double a) {
                return new Square(a).perimeter();
            }

            @Override
            public String figureName() {
                return "Square";
            }
        },
        PENTAGON {
            @Override
            public double area(double a) {
                return new Pentagon(a).area();
            }

            @Override
            public double perimeter(double a) {
                return new Pentagon(a).perimeter();
            }

            @Override
            public String figureName() {
                return "Pentagon";
            }
        },
        HEXAGON {
            @Override
            public double area(double a) {
                return new Hexagon(a).area();
            }

            @Override
            public double perimeter(double a) {
                return new Hexagon(a).perimeter();
            }

            @Override
            public String figureName() {
                return "Hexagon";
            }
        };

        public abstract double area(double a);

        public abstract double perimeter(double a);

        public abstract String figureName();

    }

    public enum TwoParameterFigureEnum implements TwoParameterFigure {
        RECTANGLE {
            @Override
            public double area(double a, double b) throws IllegalArgumentException {
                return new Rectangle(a, b).area();
            }

            @Override
            public double perimeter(double a, double b) throws IllegalArgumentException {
                return new Rectangle(a, b).perimeter();
            }

            @Override
            public String figureName() {
                return "Rectangle";
            }
        },
        RHOMBUS {
            @Override
            public double area(double a, double b) throws IllegalArgumentException {
                return new Rhombus(a, b).area();
            }

            @Override
            public double perimeter(double a, double b) throws IllegalArgumentException {
                return new Rhombus(a, b).perimeter();
            }

            @Override
            public String figureName() {
                return "Rhombus";
            }
        };

        public abstract double area(double a, double b);

        public abstract double perimeter(double a, double b);

        public abstract String figureName();
    }

}
