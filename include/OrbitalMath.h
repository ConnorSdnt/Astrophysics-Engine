//
// Created by Connor Bethel on 09/05/2026.
//

#ifndef ORBITALMATH_H
#define ORBITALMATH_H

#include <cmath>
#include <algorithm>

constexpr double PI = 3.14159265358979323846;
constexpr double EPSILON = 1e-10;

inline double toRadians(double deg) {
    return deg * (PI / 180.0);
}

inline double toDegrees(double rad) {
    return rad * (180.0 / PI);
}

inline double safeAcos(double value) {
    return std::acos(std::clamp(value, -1.0, 1.0));
}

#endif //ORBITALMATH_H
