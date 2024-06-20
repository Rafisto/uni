package parsers;

/**
 * A parser that simply returns the input string as is.
 */
public class StringParser implements Parser<String> {

    /**
     * Parses the given string and returns it as is.
     *
     * @param s the string to be parsed
     * @return the parsed string
     */
    @Override
    public String parse(String s) {
        return s;
    }
}
