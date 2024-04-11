public class Main {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: Main [circle|square|pentagon|hexagon] [first parameter]");
            System.err.println("Usage: Main [rectangle|rhombus] [first parameter] [second parameter]");
            System.exit(1);
        }

        double first = 0;
        double second = 0;

        try {
            first = Double.parseDouble(args[1]);
        } catch (NumberFormatException e) {
            System.err.println("Invalid Argument Error: " + e.getMessage());
            System.exit(1);
        }

        if (args.length == 2) {
            try {
                switch (args[0]) {
                    case "circle":
                        System.out.println("Option 'circle' selected");
                        FigureUtils.printFigureInfo(
                                Figures.SingleParameterFigureEnum.CIRCLE.figureName(),
                                Figures.SingleParameterFigureEnum.CIRCLE.area(first),
                                Figures.SingleParameterFigureEnum.CIRCLE.perimeter(first));
                        break;
                    case "square":
                        System.out.println("Option 'square' selected");
                        FigureUtils.printFigureInfo(
                                Figures.SingleParameterFigureEnum.SQUARE.figureName(),
                                Figures.SingleParameterFigureEnum.SQUARE.area(first),
                                Figures.SingleParameterFigureEnum.SQUARE.perimeter(first));
                        break;
                    case "pentagon":
                        System.out.println("Option 'pentagon' selected");
                        FigureUtils.printFigureInfo(
                                Figures.SingleParameterFigureEnum.PENTAGON.figureName(),
                                Figures.SingleParameterFigureEnum.PENTAGON.area(first),
                                Figures.SingleParameterFigureEnum.PENTAGON.perimeter(first));
                        break;
                    case "hexagon":
                        System.out.println("Option 'hexagon' selected");
                        FigureUtils.printFigureInfo(
                                Figures.SingleParameterFigureEnum.HEXAGON.figureName(),
                                Figures.SingleParameterFigureEnum.HEXAGON.area(first),
                                Figures.SingleParameterFigureEnum.HEXAGON.perimeter(first));
                        break;
                    default:
                        throw new IllegalArgumentException("Invalid option");
                }
            } catch (IllegalArgumentException e) {
                System.err.println("Invalid Argument Error: " + e.getMessage());
                System.exit(1);
            }
        } else if (args.length == 3) {
            try {
                second = Double.parseDouble(args[2]);
            } catch (NumberFormatException e) {
                System.err.println("Invalid Argument Error: " + e.getMessage());
                System.exit(1);
            }

            try {
                switch (args[0]) {
                    case "rectangle":
                        System.out.println("Option 'rectangle' selected");
                        FigureUtils.printFigureInfo(
                                Figures.TwoParameterFigureEnum.RECTANGLE.figureName(),
                                Figures.TwoParameterFigureEnum.RECTANGLE.area(first, second),
                                Figures.TwoParameterFigureEnum.RECTANGLE.perimeter(first, second));
                        break;
                    case "rhombus":
                        System.out.println("Option 'rhombus' selected");
                        FigureUtils.printFigureInfo(
                                Figures.TwoParameterFigureEnum.RHOMBUS.figureName(),
                                Figures.TwoParameterFigureEnum.RHOMBUS.area(first, second),
                                Figures.TwoParameterFigureEnum.RHOMBUS.perimeter(first, second));
                        break;
                    default:
                        throw new IllegalArgumentException("Invalid option");
                }
            } catch (IllegalArgumentException e) {
                System.err.println("Invalid Argument Error: " + e.getMessage());
                System.exit(1);
            }
        } else {
            System.out.println("Invalid number of arguments provided");
        }
    }
}
