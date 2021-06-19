//
// Created by Oliver on 07.06.21.
//

#include <array>
#include <cmath>
#include <numeric>

namespace MathUtils {
template <class T>
inline double euclideanNorm(T&& a)
{
    return std::sqrt(std::inner_product(std::cbegin(a), std::cend(a), std::cbegin(a), 0.));
}
}