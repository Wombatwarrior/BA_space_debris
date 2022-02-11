/**
 * @file DragComponent.cpp
 * @author F. Gratl
 * @date 10.02.22
 */

#include "DragComponent.h"
#include <algorithm>

double Acceleration::DragComponent::interpolateDensity(double altitude)
{
    // helper function for 2D linear interpolation at a point p between points a and b
    auto linearInterpol = [](double pX, double aX, double aY, double bX, double bY) {
        const double deltaX = bX - aX;
        const double deltaXp = pX - aX;
        const double fraction = deltaXp / deltaX;
        const double deltaY = bY - aY;
        return aY + fraction * deltaY;
    };

    if (const auto [firstAlt, firstDens] = *atmosphericDensityMap.begin();
        altitude <= firstAlt) {
        const auto [secondAlt, secondDens] = *std::next(atmosphericDensityMap.begin());
        // Use linear interpolation to extrapolate beyond the table.
        // Since this is not exactly in the intended range of operation we don't care too much about precision here.
        return linearInterpol(altitude, firstAlt, firstDens, secondAlt, secondDens);
    } else if (const auto [lastAlt, lastDens] = *std::prev(atmosphericDensityMap.end());
               altitude > lastAlt) {
        // Everything above our table is considered to be zero density
        return 0.;
    }

    // find the first table entry with a higher and lower altitude
    // and get aliases for all values in vicinity
    const auto fistHigherAltIter = std::find_if(atmosphericDensityMap.begin(), atmosphericDensityMap.end(),
        [&](const auto& mapPair) {
            const auto [tableAltitude, tableDensity] = mapPair;
            return tableAltitude > altitude;
        });
    const auto [nextAlt, nextDens] = *fistHigherAltIter;
    const auto lastLowerAltIter = std::prev(fistHigherAltIter);
    const auto [prevAlt, prevDens] = *lastLowerAltIter;

    return linearInterpol(altitude, prevAlt, prevDens, nextAlt, nextDens);
}