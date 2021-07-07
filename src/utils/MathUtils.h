//
// Created by Oliver on 07.06.21.
//

#include <array>
#include <cmath>
#include <numeric>
#include <vector>

namespace MathUtils {
/**
 * @brief Calculates the euclidean norm of a given vector
 *
 * @tparam T Type of the vector elements
 * @param a The vector
 * @return The euclidean norm of the vector a
 */
template <class T>
inline double euclideanNorm(T&& a)
{
    return std::sqrt(std::inner_product(std::cbegin(a), std::cend(a), std::cbegin(a), 0.));
}

/**
 * @brief Calculates the euclidean distance between two vectors
 *
 * @tparam T Type of the vector elements
 * @param a The first vector
 * @param b The second vector
 * @return The euclidean distance between a and b
 */
template <class T>
inline double euclideanDistance(T&& a, T&& b)
{
    std::vector<double> connection;
    auto it_b = std::cbegin(b);
    for (auto it_a = std::cbegin(a); it_a != std::cend(a); ++it_a) {
        connection.push_back(*it_a - *(it_b++));
    }
    return euclideanNorm(connection);
}

/**
 * @brief Calculates the cosine similarity between two vectors
 *
 * @tparam T Type of the vector elements
 * @param a The first vector
 * @param b The second vector
 * @return The cosine similarity between a and b
 * @returns 1 If identical
 * @returns 0 If orthogonal
 * @returns -1 If exact opposites
 */
template <class T>
inline double cosSimilarity(T&& a, T&& b)
{
    return std::inner_product(std::cbegin(a), std::cend(a), std::cbegin(b), 0.) / (euclideanNorm(a) * euclideanNorm(b));
}
}