#include <stringConverter.hpp>

#include <cmath>
#include <cassert>

void testStringConverter() noexcept(true);

static void testStringConverterNormalCase() noexcept(true)
{
    assert(StringConverter::stringToVal<int>("0") == 0);
    assert(StringConverter::stringToVal<int>("123") == 123);
    assert(StringConverter::stringToVal<int>("-123") == -123);
    assert(StringConverter::stringToVal<int>("12345678") == 12345678);

    assert(StringConverter::stringToVal<unsigned long>("0") == 0UL);
    assert(StringConverter::stringToVal<unsigned long>("123") == 123UL);
    assert(StringConverter::stringToVal<unsigned long>("-123") == static_cast<unsigned long>(-123));
    assert(StringConverter::stringToVal<unsigned long>("12345678") == 12345678UL);

    assert(std::fabs(StringConverter::stringToVal<double>("0") - 0.0) < 0.00001);
    assert(std::fabs(StringConverter::stringToVal<double>("0.11") - 0.11) < 0.00001);
    assert(std::fabs(StringConverter::stringToVal<double>("-3.14") - -3.14) < 0.00001);
    assert(std::fabs(StringConverter::stringToVal<double>("123456.789") - 123456.789) < 0.00001);
}

template <typename T>
static void testStringConverterExceptions(const std::string &str) noexcept(true)
{
    try
    {
        const T val = StringConverter::stringToVal<T>(str);
        (void)val;
        assert(false && "Exception should be raised");
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
    }
}

void testStringConverter() noexcept(true)
{
    testStringConverterNormalCase();

    testStringConverterExceptions<unsigned int>(std::string("ala"));
    testStringConverterExceptions<unsigned int>(std::string("a1"));
    testStringConverterExceptions<unsigned int>(std::string("1a1"));
    testStringConverterExceptions<unsigned int>(std::string("1a"));

    testStringConverterExceptions<long>(std::string("ala"));
    testStringConverterExceptions<long>(std::string("a1"));
    testStringConverterExceptions<long>(std::string("1a1"));
    testStringConverterExceptions<long>(std::string("1a"));

    testStringConverterExceptions<double>(std::string("ala"));
    testStringConverterExceptions<double>(std::string("a1.0"));
    testStringConverterExceptions<double>(std::string("1.a1"));
    testStringConverterExceptions<double>(std::string("1.1a"));
}