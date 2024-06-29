package parsers;

/**
 * A parser implementation for parsing integers from strings.
 */
public class IntegerParser implements Parser<Integer> {
    /**
     * Parses the given string into an Integer object.
     *
     * @param s the string to be parsed
     * @return the parsed Integer object
     * @throws NumberFormatException if the string cannot be parsed as an integer
     */
    @Override
    public Integer parse(String s) {
        return Integer.parseInt(s);
    }
}
