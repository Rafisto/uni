import java.util.Arrays;

public class TestBinomials {
    private TestBinomials() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    private static void testBinomialsNormalCase() {
        try {
            assert Binomials.generateRow(0).equals(Arrays.asList(1));
            assert Binomials.generateRow(1).equals(Arrays.asList(1, 1));
            assert Binomials.generateRow(2).equals(Arrays.asList(1, 2, 1));
            assert Binomials.generateRow(3).equals(Arrays.asList(1, 3, 3, 1));
            assert Binomials.generateRow(4).equals(Arrays.asList(1, 4, 6, 4, 1));
            assert Binomials.generateRow(5).equals(Arrays.asList(1, 5, 10, 10, 5, 1));
            assert Binomials.generateRow(6).equals(Arrays.asList(1, 6, 15, 20, 15, 6, 1));
            assert Binomials.generateRow(7).equals(Arrays.asList(1, 7, 21, 35, 35, 21, 7, 1));
            assert Binomials.generateRow(8).equals(Arrays.asList(1, 8, 28, 56, 70, 56, 28, 8, 1));
            assert Binomials.generateRow(9).equals(Arrays.asList(1, 9, 36, 84, 126, 126, 84, 36, 9, 1));
            assert Binomials.generateRow(10).equals(Arrays.asList(1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1));
        } catch (IllegalArgumentException e) {
            System.out.println("Exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void testBinomialsExceptions(int n) {
        try {
            Binomials.generateRow(n);
            System.out.println("Test failed: No exception thrown for input: " + n);
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
    }

    public static void testBinomials() {
        testBinomialsNormalCase();

        testBinomialsExceptions(-1);
    }
}
