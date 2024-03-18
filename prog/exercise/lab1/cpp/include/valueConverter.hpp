#ifndef VALUE_CONVERTER_HPP
#define VALUE_CONVERTER_HPP

#include <string>
#include <sstream>
#include <stdexcept>

/**
 * @class ValueConverter
 *
 * @brief A static class that converts values from string to int, unsigned int, long, double, etc.
 */
class ValueConverter
{
public:
    ValueConverter() = delete;
    ~ValueConverter() = delete;
    /**
     * @brief Converts a string to a value of type T
     *
     * @tparam T The type of the value to convert to
     * @param str The string to convert
     * @return The value of type T
     * @throw std::invalid_argument if the conversion fails
     */
    template <typename T>
    static T stringToValue(const std::string &str) noexcept(false)
    {
        T val = {};
        char c = {};

        std::stringstream ss(str);
        ss >> val;

        if (ss.fail() || ss.get(c))
        {
            throw std::invalid_argument(std::string("Cannot convert ") + str + " to " + typeid(T).name());
        }

        return val;
    } 
};

#endif