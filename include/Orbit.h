//
// Created by Connor Bethel on 06/05/2026.
//

#ifndef ORBIT_H
#define ORBIT_H
#include <string>

class Orbit{
public:
    Orbit(std::string body_name, double sma, double ecc, double inc, double raan, double aop, double anom, double gm);

    [[nodiscard]] std::string getBodyName() const;
    [[nodiscard]] double getSma() const;
    [[nodiscard]] double getEcc() const;
    [[nodiscard]] double getInc() const;
    [[nodiscard]] double getRaan() const;
    [[nodiscard]] double getAop() const;
    [[nodiscard]] double getAnom() const;
    [[nodiscard]] double getGm() const;
    [[nodiscard]] double getPeriod() const;
    [[nodiscard]] double getRadius() const;
    [[nodiscard]] double getPeriapsisRadius() const;
    [[nodiscard]] double getApoapsisRadius() const;
    [[nodiscard]] double getSpeed() const;
    [[nodiscard]] double getSpecificOrbitalEnergy() const;

private:
    const std::string body_name; // Will be a reference to the specific body in the future
    const double sma; // Semi-major Axis (a>0)
    const double ecc; // Eccentricity (e>=0)
    const double inc; // Inclination [0-180]
    const double raan; // RAAN Right Ascension of the Ascending Node [0-360]
    const double aop; // Argument of Periapsis [0-360]
    const double anom; // True anomaly [0-360]
    const double gm; // Gravitational Parameter of body of orbit
};

#endif //ORBIT_H
