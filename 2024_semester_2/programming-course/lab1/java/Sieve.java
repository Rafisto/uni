import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public final class Sieve {
    private Sieve() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    public static List<Integer> primes(int n) throws IllegalArgumentException {
        if (n < 2) {
            throw new IllegalArgumentException("Parameter n should be >= 2, got " + n);
        }

        boolean[] isPrime = new boolean[n + 1];
        Arrays.fill(isPrime, true);
        List<Integer> primes = new ArrayList<>();

        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primes.add(i);
                for (long j = (long) i * i; j <= (long)n; j += i) {
                    isPrime[(int) j] = false;
                }
            }
        }

        return primes;
    }
}
