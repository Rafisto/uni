
public final class Test {
    private Test() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    public static void main(final String[] args) {
        TestBinomials.testBinomials();
        TestPacalTriangleRow.testPascalTrianleRow();
    }
}