//
// Created by Connor Bethel on 07/05/2026.
//

#ifndef STATEVECTOR_H
#define STATEVECTOR_H

class StateVector;

StateVector operator*(double scalar, const StateVector& sv);

class StateVector {
public:
    StateVector(double x, double y, double z, double vx, double vy, double vz);

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] double getZ() const;
    [[nodiscard]] double getVX() const;
    [[nodiscard]] double getVY() const;
    [[nodiscard]] double getVZ() const;
    [[nodiscard]] double getSpeed() const;
    [[nodiscard]] double getRadius() const;

    StateVector operator + (const StateVector& other) const;
    StateVector operator * (double scalar) const;
private:
    const double x;
    const double y;
    const double z;
    const double vx;
    const double vy;
    const double vz;
};



#endif //STATEVECTOR_H
