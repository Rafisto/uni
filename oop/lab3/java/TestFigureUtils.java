public class TestFigureUtils {
    private static void testFigureUtilsNormalCase() {
        assert true == FigureUtils.isSquare(4, 4, 4, 4, 90);
        assert false == FigureUtils.isSquare(4, 4, 4, 4, 45);
        assert false == FigureUtils.isSquare(4, 4, 4, 5, 90);
        assert true == FigureUtils.isRhombus(4, 4, 4, 4, 60);
        assert false == FigureUtils.isRhombus(4, 4, 4, 5, 60);
        assert true ==  FigureUtils.isRectangle(4, 4, 5, 5, 90);
        assert false == FigureUtils.isRectangle(4, 4, 5, 5, 45);
        assert false == FigureUtils.isRectangle(4, 4, 4, 4, 90);
    }

    public static void testFigureUtils() {
        testFigureUtilsNormalCase();
    }
}
