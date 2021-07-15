//
// Created by Oliver on 13.05.21.
//

#pragma once
#include <vector>

#include "Debris.h"
namespace Debris {
/**
 * @class DebrisContainer
 * @brief Holds a vector of Debris objects
 */
template <class D>
class DebrisContainer {
public:
    /**
     * @brief Default constructor
     *
     * Creates a new DebrisContainer object and initializes the #debris_vector
     * empty
     */
    DebrisContainer();

    /**
     * @brief Default destructor
     *
     * Destroy DebrisContainer object
     */
    virtual ~DebrisContainer();

    auto begin()
    {
        return debris_vector.begin();
    }

    auto end()
    {
        return debris_vector.end();
    }

    const auto cbegin() const
    {
        return debris_vector.cbegin();
    }

    const auto cend() const
    {
        return debris_vector.cend();
    }

    /**
     * @brief Adds a Debris object to the #debris_vector
     *
     * Adds a copy of the given Debris object to the end of the #debris_vector
     *
     * @param debris Reference to the Debris object to add
     */
    void addDebris(const D& debris);

    /**
     * @brief Clear the #debris_vector
     *
     * Remove all Debris objects from the #debris_vector by calling it's clear()
     * function
     *
     */
    void cleanDebrisVector();

private:
    std::vector<D> debris_vector; /**< std::vector holding the Debris objects
                                      this DebrisContainer objects holds */
public:
    /**
     * @brief Getter function for #debris_vector vector
     *
     * @return Value of #debris_vector
     */
    [[nodiscard]] const std::vector<D>& getDebrisVector() const;
    std::vector<D>& getDebrisVector();

    /**
     * @brief Setter function for #debris_vector
     *
     * @param debrisVector New value of #debris_vector
     */
    void setDebrisVector(std::vector<D>& debrisVector);
};
template <class D>
DebrisContainer<D>::DebrisContainer() = default;

template <class D>
DebrisContainer<D>::~DebrisContainer() = default;

template <class D>
void DebrisContainer<D>::addDebris(const D& debris)
{
    debris_vector.push_back(debris);
}

template <class D>
void DebrisContainer<D>::cleanDebrisVector()
{
    debris_vector.clear();
}

template <class D>
const std::vector<D>& DebrisContainer<D>::getDebrisVector() const
{
    return debris_vector;
}

template <class D>
std::vector<D>& DebrisContainer<D>::getDebrisVector()
{
    return debris_vector;
}

template <class D>
void DebrisContainer<D>::setDebrisVector(std::vector<D>& debrisVector)
{
    debris_vector = debrisVector;
}
} // namespace Debris
