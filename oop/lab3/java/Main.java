public class Main {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: Main [o|c|p|s] [at least one additional argument...]");
            System.exit(1);
        }
        
        Figure figure = null;

        switch (args[0].charAt(0)) {
            case 'o':
                System.out.println("Option o selected");
                try {
                    double radius = Double.parseDouble(args[1]);
                    figure = new Circle(radius);
                } catch (IllegalArgumentException e) {
                    System.err.println("Invalid Argument Error: " + e.getMessage());
                    System.exit(1);
                }
                break;
            case 'c':
                System.out.println("Option c selected");
                if (args.length < 6) {
                    System.err.println("4 side lengths and angle not provided.");
                    System.exit(1);
                }
                try {
                    double side1 = Double.parseDouble(args[1]);
                    double side2 = Double.parseDouble(args[2]);
                    double side3 = Double.parseDouble(args[3]);
                    double side4 = Double.parseDouble(args[4]);
                    double angle = Double.parseDouble(args[5]);
                    if (FigureUtils.isSquare(side1, side2, side3, side4, angle)) {
                        figure = new Square(side1);
                    } else if (FigureUtils.isRhombus(side1, side2, side3, side4, angle)) {
                        figure = new Rhombus(side1, angle);
                    } else if (FigureUtils.isRectangle(side1, side2, side3, side4, angle)) {
                        if (Math.abs(side1 - side2) < 1e-6 && Math.abs(side3 - side4) < 1e-6) {
                            figure = new Rectangle(side1, side3);
                        } else if ((Math.abs(side1 - side3) < 1e-6 && Math.abs(side2 - side4) < 1e-6) || (Math.abs(side1 - side4) < 1e-6 && Math.abs(side2 - side3) < 1e-6)) {
                            figure = new Rectangle(side1, side2);
                        } else {
                            throw new IllegalArgumentException("Invalid Rectangle: There should be at least 2 pairs of equal side lengths");
                        }
                    } else {
                        throw new IllegalArgumentException("Invalid Quadrilateral.");
                    }
                } catch (IllegalArgumentException e) {
                    System.err.println("Invalid Argument Error: " + e.getMessage());
                    System.exit(1);
                }
                break;
            case 'p':
                System.out.println("Option p selected");
                try {
                    double sideLength = Double.parseDouble(args[1]);
                    figure = new Pentagon(sideLength);
                } catch (IllegalArgumentException e) {
                    System.err.println("Invalid Argument Error: " + e.getMessage());
                    System.exit(1);
                }
                break;
            case 's':
                System.out.println("Option s selected");
                try {
                    double sideLength = Double.parseDouble(args[1]);
                    figure = new Hexagon(sideLength);
                } catch (IllegalArgumentException e) {
                    System.err.println("Invalid Argument Error: " + e.getMessage());
                    System.exit(1);
                }
                break;
            default:
                System.err.println("Invalid Figure option");
                System.exit(1);
        }

        FigureUtils.printFigureInfo(figure);
    }
}
