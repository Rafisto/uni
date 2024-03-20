import java.util.ArrayList;
import java.util.List;

public class Binomials {
    public static List<Integer> generateRow(int n) throws IllegalArgumentException {
        if (n < 0) {
            throw new IllegalArgumentException("Parameter n should be >= 0, got " + n);
        }

        List<Integer> row = new ArrayList<>();
        row.add(1);

        long prev = 1;
        for (int i = 1; i <= n; i++) {
            long curr = prev * (n - i + 1) / i;
            row.add((int) curr);
            prev = curr;
        }

        return row;
    }
}
