//
// Created by Connor Bethel on 07/05/2026.
//

#include "StateVector.h"
#include <cmath>

StateVector::StateVector(const double x, const double y, const double z, const double vx, const double vy, const double vz)
    : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz)
{
}

double StateVector::getX() const {
    return x;
}

double StateVector::getY() const {
    return y;
}

double StateVector::getZ() const {
    return z;
}

double StateVector::getVX() const {
    return vx;
}

double StateVector::getVY() const {
    return vy;
}

double StateVector::getVZ() const {
    return vz;
}

double StateVector::getSpeed() const {
    return std::sqrt(vx * vx + vy * vy + vz * vz);
}

double StateVector::getRadius() const {
    return std::sqrt(x * x + y * y + z * z);
}

StateVector operator*(double scalar, const StateVector &sv) {
    return sv * scalar;
}

StateVector StateVector::operator+(const StateVector &other) const {
    return {x + other.x, y + other.y, z + other.z, vx + other.vx, vy + other.vy, vz + other.vz};
}

StateVector StateVector::operator*(double scalar) const {
    return {x * scalar, y * scalar, z * scalar, vx * scalar, vy * scalar, vz * scalar};
}



