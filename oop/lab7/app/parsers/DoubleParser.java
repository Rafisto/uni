package parsers;

/**
 * A parser implementation for parsing strings into Double values.
 */
public class DoubleParser implements Parser<Double> {
    /**
     * Parses the given string into a Double value.
     *
     * @param s the string to be parsed
     * @return the parsed Double value
     * @throws NumberFormatException if the string cannot be parsed into a Double
     */
    @Override
    public Double parse(String s) {
        return Double.parseDouble(s);
    }
}
