import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: Main <arg1> <arg2> ...");
            System.exit(1);
        }

        PascalTriangleRow p = null;

        try {
            int initArgument = Integer.parseInt(args[0]);
            p = new PascalTriangleRow(initArgument);
        } catch (IllegalArgumentException e) {
            System.err.println("Invalid Argument Error: " + e.getMessage());
            System.exit(1);
        }

        System.out.println("Successfully initialized PascalTriangleRow.");

        for (int i = 1; i < args.length; i++) {
            try {
                int argNumber = Integer.parseInt(args[i]);
                int prime = p.getCoefficient(argNumber);

                System.out.println(argNumber + " --> " + prime);
            } catch (NumberFormatException e) {
                System.err.println("Invalid Argument Error: " + e.getMessage());
            } catch (IndexOutOfBoundsException e) {
                System.err.println("Out of Range Error: " + e.getMessage());
            } catch (IllegalArgumentException e) {
                System.err.println("Invalid Argument Error: " + e.getMessage());
            }
        }
    }
}