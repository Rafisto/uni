extern void testUtils() noexcept(true);
extern void testHexagon() noexcept(true);
extern void testPentagon() noexcept(true);
extern void testCircle() noexcept(true);
extern void testQuadrilaterals() noexcept(true);
extern void testStringConverter() noexcept(true);

int main()
{
    testUtils();
    testHexagon();
    testPentagon();
    testCircle();
    testQuadrilaterals();
    testStringConverter();

    return 0;
}