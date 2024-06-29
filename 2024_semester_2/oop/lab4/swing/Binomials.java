import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class Binomials {
    public static List<BigInteger> generateRow(int n) throws IllegalArgumentException {
        if (n < 0) {
            throw new IllegalArgumentException("Parameter n should be >= 0, got " + n);
        }

        List<BigInteger> row = new ArrayList<>();
        row.add(BigInteger.ONE);

        BigInteger prev = BigInteger.ONE;
        for (int i = 1; i <= n; i++) {
            BigInteger curr = prev.multiply(BigInteger.valueOf(n - i + 1)).divide(BigInteger.valueOf(i));
            if (curr.compareTo(BigInteger.ZERO) < 0) {
                throw new IllegalArgumentException("Parameter " + n + " causes an integer overflow at " + i + "-th iteration");
            }
            row.add(curr);
            prev = curr;
        }

        return row;
    }
}
