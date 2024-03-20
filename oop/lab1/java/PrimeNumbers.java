import java.util.List;

public class PrimeNumbers {
    private List<Integer> primes;

    public PrimeNumbers(final int n) throws IllegalArgumentException {
        if (n < 2) {
            throw new IllegalArgumentException("Invalid argument: " + n);
        }
        this.primes = Sieve.primes(n);
    }

    public int getPrime(int m) throws IllegalArgumentException, IndexOutOfBoundsException {
        if (m < 0) {
            throw new IllegalArgumentException("Index must be greater or equal to 0. Got " + m + " instead.");
        }
        if (m >= this.primes.size()) {
            throw new IndexOutOfBoundsException("Range exceeded. Index must be less than or equal to "
                    + (this.primes.size() - 1) + ". Got " + m + " instead.");
        }

        return this.primes.get(m);
    }

    public int getCount() {
        return this.primes.size();
    }
}
