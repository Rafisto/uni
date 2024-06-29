public class TestPrimeNumbers {
    private TestPrimeNumbers() throws InstantiationError
    {
        throw new InstantiationError("This is a static class!");
    }

    static public void testPrimeNumbers() {
        testPrimeNumbersNormalCase();

        testPrimeNumbersExceptions(0);
        testPrimeNumbersExceptions(1);
        testPrimeNumbersExceptions(-1);
        testPrimeNumbersExceptions(-420);
        testPrimeNumbersExceptions(-2137);

        testPrimeNumbersGetExceptions(5);
        testPrimeNumbersGetExceptions(-2);
        testPrimeNumbersGetExceptions(-1);
    }

    static private void testPrimeNumbersNormalCase() {
        try {
            PrimeNumbers p = new PrimeNumbers(2);
            assert p.getPrime(0) == 2;
            assert p.getCount() == 1;
        } catch (AssertionError e) {
            System.out.println("Test failed: " + e.getMessage());
        }

        try {
            PrimeNumbers p = new PrimeNumbers(3);
            assert p.getPrime(0) == 2;
            assert p.getPrime(1) == 3;
            assert p.getCount() == 2;
        } catch (AssertionError e) {
            System.out.println("Test failed: " + e.getMessage());
        }

        try {
            PrimeNumbers p = new PrimeNumbers(420);
            assert p.getPrime(0) == 2;
            assert p.getPrime(10) == 31;
            assert p.getPrime(80) == 419;
            assert p.getCount() == 81;
        } catch (AssertionError e) {
            System.out.println("Test failed: " + e.getMessage());
        }

        try {
            PrimeNumbers p = new PrimeNumbers(2137);
            assert p.getPrime(0) == 2;
            assert p.getPrime(10) == 31;
            assert p.getPrime(100) == 547;
            assert p.getPrime(300) == 1993;
            assert p.getCount() == 322;
        } catch (AssertionError e) {
            System.out.println("Test failed: " + e.getMessage());
        }
    }

    static private void testPrimeNumbersExceptions(int val) {
        try {
            PrimeNumbers primes = new PrimeNumbers(val);
            assert false : "Exception should be raised";
        } catch (IllegalArgumentException e) {
            // Exception caught as expected
        }
    }

    static private void testPrimeNumbersGetExceptions(int val) {
        try {
            PrimeNumbers p = new PrimeNumbers(2);
            p.getPrime(val);
            assert false : "Exception should be raised";
        } catch (IllegalArgumentException e) {
            // Exception caught as expected
        } catch (IndexOutOfBoundsException e) {
            // Exception caught as expected
        }
    }
}
