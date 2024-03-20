import java.util.List;

public class TestSieve {
    private TestSieve() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    public static void testSieve() {
        testSieveNormalCase();

        testSieveExceptions(0);
        testSieveExceptions(1);
        testSieveExceptions(-1);
        testSieveExceptions(-420);
        testSieveExceptions(-2137);
        testSieveExceptions(-1000000);
    }

    private static void testSieveNormalCase() {
        assert Sieve.primes(2).equals(List.of(2));
        assert Sieve.primes(3).equals(List.of(2, 3));
        assert Sieve.primes(10).equals(List.of(2, 3, 5, 7));
        assert Sieve.primes(100).equals(List.of(
                2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                31, 37, 41, 43, 47, 53, 59, 61, 67,
                71, 73, 79, 83, 89, 97));
    }

    private static void testSieveExceptions(int val) {
        try {
            Sieve.primes(val);
            assert false : "Exception should be raised";
        } catch (IllegalArgumentException e) {
            // Shall not be run
        } catch (IndexOutOfBoundsException e) {
            // Shall not be run
        }
    }

}
