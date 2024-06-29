package parsers;

/**
 * The Parser interface represents a generic parser that can parse a string into an object of type T.
 *
 * @param <T> the type of object that the parser can parse the string into
 */
public interface Parser<T> {
    /**
     * Parses the given string into an object of type T.
     *
     * @param s the string to be parsed
     * @return the parsed object of type T
     */
    T parse(String s);
}
