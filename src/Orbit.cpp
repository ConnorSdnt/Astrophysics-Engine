//
// Created by Connor Bethel on 06/05/2026.
//

#include "Orbit.h"
#include <stdexcept>

constexpr double PI = 3.14159265358979323846;

Orbit::Orbit(std::string body_name, double sma, double ecc, double inc, double raan, double aop, double anom, double gm)
    : body_name(std::move(body_name)), sma(sma), ecc(ecc), inc(inc), raan(raan), aop(aop), anom(anom), gm(gm)
{
    if (sma <= 0) {
        throw std::invalid_argument("sma must be > 0");
    }
    if (ecc < 0) {
        throw std::invalid_argument("ecc must be >= 0");
    }
    if (inc < 0 || inc > 180) {
        throw std::invalid_argument("inc must be 0 <= inc <= 180");
    }
    if (raan < 0 || raan > 360) {
        throw std::invalid_argument("raan must be 0 <= raan <= 360");
    }
    if (aop < 0 || aop > 360) {
        throw std::invalid_argument("aop must be 0 <= aop <= 360");
    }
    if (anom < 0 || anom > 360) {
        throw std::invalid_argument("anom must be 0 <= aop <= 360");
    }
    if (gm < 0) {
        throw std::invalid_argument("gm must be > 0");
    }
}

std::string Orbit::getBodyName() const {
    return body_name;
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

double Orbit::getGm() const {
    return gm;
}

double Orbit::getPeriod() const {
    const double period = 2 * PI * std::sqrt(sma * sma * sma / gm);
    return period;
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
    const double r = sma * (1.0 + ecc);
    return r;
}

double Orbit::getSpeed() const {
    const double r = getRadius();
    const double speed = std::sqrt(gm * (2.0/r - 1.0/sma));
    return speed;
}

double Orbit::getSpecificOrbitalEnergy() const {
    const double speed = getSpeed();
    const double radius = getRadius();
    const double E = speed * speed / 2.0 - gm / radius;
    return E;
}




