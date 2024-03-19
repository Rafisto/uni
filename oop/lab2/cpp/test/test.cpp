extern void testBinomials() noexcept(true);
extern void testPascalTriangleRow() noexcept(true);
extern void testStringConverter() noexcept(true);

int main()
{
    testStringConverter();
    testPascalTriangleRow();
    testBinomials();

    return 0;
}