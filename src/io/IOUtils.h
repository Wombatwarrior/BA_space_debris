//
// Created by Oliver on 15.05.21.
//

#pragma once
#include <iostream>
#include <string>
#include <array>
#include <sstream>

/**
 * @namespace IOUtils
 *
 * @brief Contains utility functions for general io operations
 */
namespace IOUtils {
    /**
     * @brief Converts a 3D vector of doubles into a readable string representation
     *
     * @param array Reference to the 3D vector to convert
     * @return String representation of the given 3D vector
     */
    inline std::string array3DToString(const std::array<double,3> &array) {
        std::ostringstream result;
        result << "[" << array[0] << ", " << array[1] << ", " << array[2] << "]";
        return result.str();
    }
    /**
      * @brief write a 3D vector of doubles into a csv format to output file stream
      *
      * @param array Reference to the 3D vector to convert
      * @param out Output file stream to write to
      */
    inline void array3DToCSV(std::ostream &out, const std::array<double,3> &array) {
        out << array[0] << "," << array[1] << "," << array[2];
    }
}