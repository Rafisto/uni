import java.util.ArrayList;
import java.util.List;

public class PascalTriangleRow {
    private final List<Integer> row;

    public PascalTriangleRow(int n) throws IllegalArgumentException {
        if (n < 0) {
            throw new IllegalArgumentException("Invalid argument: " + n);
        }
        try {
            this.row = Binomials.generateRow(n);
        } catch (Exception e) {
            throw new IllegalArgumentException(e.getMessage());
        }
    }

    public int getCoefficient(int m) throws IllegalArgumentException, IndexOutOfBoundsException {
        if (m < 0) {
            throw new IllegalArgumentException("Index must be greater or equal to 0. Got " + m + " instead.");
        }
        if (m >= this.row.size()) {
            throw new IndexOutOfBoundsException("Range exceeded. Index must be less than or equal to "
                    + (this.row.size() - 1) + ". Got " + m + " instead.");
        }

        return this.row.get(m);
    }
}