//
// Created by Oliver on 15.05.21.
//

#include <iostream>
#include <string>
#include <array>
#include <sstream>

namespace Output {
    std::string array3DToString(const std::array<double,3> &array) {
        std::ostringstream result;
        result << "[" << array[0] << ", " << array[1] << ", " << array[2] << "[";
        return result.str();
    }
}

namespace Input {

}