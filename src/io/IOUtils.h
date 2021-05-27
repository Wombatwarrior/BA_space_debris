//
// Created by Oliver on 15.05.21.
//

#pragma once
#include <array>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @namespace IOUtils
 *
 * @brief Contains utility functions for general io operations
 */
namespace IOUtils {
/**
 * @brief Converts a 3D vector of doubles into a readable string representation
 * @deprecated
 * @param array Reference to the 3D vector to convert
 * @return String representation of the given 3D vector
 */
inline std::string array3DToString(const std::array<double, 3>& array)
{
    std::ostringstream result;
    result << "[" << array[0] << ", " << array[1] << ", " << array[2] << "]";
    return result.str();
}
/**
 * @brief write a 3D vector of doubles into a csv format to output file stream
 * @deprecated
 * @param array Reference to the 3D vector to convert
 * @param out Output file stream to write to
 */
inline void array3DToCSV(std::ostream& out,
    const std::array<double, 3>& array)
{
    out << array[0] << "," << array[1] << "," << array[2];
}

/**
 * Formatted output of a container which fulfills the Container requirement
 * (provide cbegin() and cend()) to a given ostring .
 * @tparam T Type of Container.
 * @param a Container.
 * @param out ostream to output the result to
 * @param delimiter String that is put between items.
 * @param surround Strings to be put before and after the listing (e.g.
 * brackets).
 */
template <class T>
void to_ostream(T&& a,
    std::ostream& out = std::cout,
    const std::string& delimiter = ",",
    const std::array<std::string, 2>& surround = { "", "" })
{
    auto it = std::cbegin(a);
    const auto end = std::cend(a);
    if (it == end) {
        out << surround[0] + surround[1];
    }
    out << surround[0] << *it;
    for (++it; it != end; ++it) {
        out << delimiter << *it;
    }
    out << surround[1];
}

/**
 * Generates a string representation of a container which fulfills the
 * Container requirement (provide cbegin and cend).
 * @tparam T Type of Container.
 * @param a Container.
 * @param delimiter String that is put between items.
 * @param surround Strings to be put before and after the listing (e.g.
 * brackets).
 * @return String representation of a.
 */
template <class T>
std::string to_string(T&& a,
    const std::string& delimiter = ", ",
    const std::array<std::string, 2>& surround = { "[", "]" })
{
    std::ostringstream strStream;
    to_ostream(a, strStream, delimiter, surround);
    return strStream.str();
}
} // namespace IOUtils