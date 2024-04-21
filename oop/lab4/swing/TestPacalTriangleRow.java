import java.util.List;

public class TestPacalTriangleRow {
    private TestPacalTriangleRow() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    private static void testPascalTriangleRowNormalCase() {
        try {
            PascalTriangleRow p0 = new PascalTriangleRow(0);
            assert p0.getCoefficient(0) == 1;

            PascalTriangleRow p1 = new PascalTriangleRow(1);
            assert p1.getCoefficient(0) == 1;
            assert p1.getCoefficient(1) == 1;

            PascalTriangleRow p2 = new PascalTriangleRow(2);
            assert p2.getCoefficient(0) == 1;
            assert p2.getCoefficient(1) == 2;
            assert p2.getCoefficient(2) == 1;

            PascalTriangleRow p3 = new PascalTriangleRow(3);
            assert p3.getCoefficient(0) == 1;
            assert p3.getCoefficient(1) == 3;
            assert p3.getCoefficient(2) == 3;
            assert p3.getCoefficient(3) == 1;

            PascalTriangleRow p4 = new PascalTriangleRow(4);
            assert p4.getCoefficient(0) == 1;
            assert p4.getCoefficient(1) == 4;
            assert p4.getCoefficient(2) == 6;
            assert p4.getCoefficient(3) == 4;
            assert p4.getCoefficient(4) == 1;

            PascalTriangleRow p20 = new PascalTriangleRow(20);
            assert p20.getCoefficient(0) == 1;
            assert p20.getCoefficient(1) == 20;
            assert p20.getCoefficient(2) == 190;
            assert p20.getCoefficient(3) == 1140;
        } catch (IllegalArgumentException e) {
            System.out.println("Exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void testPascalTriangleRowExceptions(int val) {
        try {
            PascalTriangleRow p = new PascalTriangleRow(val);
            System.out.println("Test failed: No exception thrown for input: " + val);
        } catch (IllegalArgumentException e) {
            // Expected exception
        }
    }

    
    public static void testPascalTrianleRow() {
        testPascalTriangleRowNormalCase();

        testPascalTriangleRowExceptions(-1);
        testPascalTriangleRowExceptions(-20);
    }
}
