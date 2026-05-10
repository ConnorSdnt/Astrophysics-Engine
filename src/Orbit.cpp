//
// Created by Connor Bethel on 06/05/2026.
//

#include "Orbit.h"
#include <stdexcept>
#include <cmath>

constexpr double PI = 3.14159265358979323846;

Orbit::Orbit(const CelestialBody& body, double sma, double ecc, double inc, double raan, double aop, double anom)
    : body(body), sma(sma), ecc(ecc), inc(inc), raan(raan), aop(aop), anom(anom)
{
    // Handle all types of orbit
    if (0.0 <= ecc && ecc < 1.0) { // Elliptical
        if (sma < 0.0) {
            throw std::invalid_argument("Semi-major Axis cannot be less than 0 for an elliptical orbit");
        }
    } else if (std::abs(ecc - 1.0) < 1e-10) { // Parabolic
        throw std::invalid_argument("Parabolic orbits (ecc=1) are not supported");
    } else if (1.0 < ecc) { // Hyperbolic
        if (sma > 0.0) {
            throw std::invalid_argument("Semi-major Axis cannot be greater than 0 for an elliptical orbit");
        }
        if (ecc > 1.0) {
            const double max_anom_rad = std::acos(-1.0 / ecc);
            const double max_anom_deg = max_anom_rad * (180.0 / PI);
            const double anom_centered = anom > 180.0 ? anom - 360.0 : anom;
            if (std::abs(anom_centered) >= max_anom_deg) {
                throw std::invalid_argument(
                    "True anomaly exceeds asymptotic limit for hyperbolic orbit");
            }
        }
    } else { // ecc < 0: Not valid
        throw std::invalid_argument("Eccentricity cannot be less than 0");
    }

    if (inc < -1.0 || 180 < inc) {
        throw std::invalid_argument("Inclination must be in the range \'0 <= inc <= 180\'");
    }
    if (raan < 0 || 360 <= raan) {
        throw std::invalid_argument(R"('Right ascension of ascending node' must be in the range '0 <= raan < 360')");
    }
    if (aop < 0 || 360 <= aop) {
        throw std::invalid_argument(R"('Argument of periapsis' must be in the range '0 <= aop < 360')");
    }
    if (anom < 0 || 360 <= anom) {
        throw std::invalid_argument(R"('True anomaly' must be in the range '0 <= anom < 360')");
    }
}

const CelestialBody& Orbit::getBody() const {
    return body;
}

double Orbit::getSma() const {
    return sma;
}

double Orbit::getEcc() const {
    return ecc;
}

double Orbit::getInc() const {
    return inc;
}

double Orbit::getRaan() const {
    return raan;
}

double Orbit::getAop() const {
    return aop;
}

double Orbit::getAnom() const {
    return anom;
}

double Orbit::getPeriod() const {
    if (ecc > 1.0) return 0.0; // hyperbolic — no period
    return 2.0 * PI * std::sqrt(sma * sma * sma / body.getGm());
}

double Orbit::getRadius() const {
    const double anom_rad = anom * (PI / 180.0);
    const double r = sma * (1.0 - ecc * ecc) / (1.0 + ecc * std::cos(anom_rad));
    return r;
}

double Orbit::getPeriapsisRadius() const {
    const double r = sma * (1.0 - ecc);
    return r;
}

double Orbit::getApoapsisRadius() const {
    if (ecc >= 1.0) return 0.0; // hyperbolic — no apoapsis
    return sma * (1.0 + ecc);
}

double Orbit::getSpeed() const {
    const double r = getRadius();
    const double speed = std::sqrt(body.getGm() * (2.0/r - 1.0/sma));
    return speed;
}

double Orbit::getSpecificOrbitalEnergy() const {
    const double speed = getSpeed();
    const double radius = getRadius();
    const double E = speed * speed / 2.0 - body.getGm() / radius;
    return E;
}




