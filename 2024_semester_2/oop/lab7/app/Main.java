import parsers.*;
import view.CLI;

/**
 * The Main class is the entry point of the program.
 */
public class Main {
    /**
     * The main method is the entry point of the program.
     * It prompts the user to choose a tree type (integer, double, or string),
     * creates the corresponding parser and CLI object, and runs the CLI.
     * 
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println("Which tree type do you want to create?"); 
        System.out.println("(i)nteger, (d)ouble, (s)tring");
        char type = System.console().readLine().charAt(0);
        switch(type) {
            case 'i':
                Parser<Integer> intParser = new IntegerParser();
                CLI<Integer> intCLI = new CLI<Integer>(intParser);
                intCLI.run();
                break;
            case 'd':
                Parser<Double> doubleParser = new DoubleParser();
                CLI<Double> doubleCLI = new CLI<Double>(doubleParser);
                doubleCLI.run();
                break;
            case 's':
                Parser<String> stringParser = new StringParser();
                CLI<String> stringCLI = new CLI<String>(stringParser);
                stringCLI.run();
                break;
            default:
                System.out.println("Invalid type");
        }
    }
}
