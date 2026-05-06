//
// Created by Connor Bethel on 06/05/2026.
//

#include "CelestialBody.h"
#include <unordered_map>
#include <stdexcept>

CelestialBody::CelestialBody(std::string  name, double gm, double mean_radius_km, double soi_radius_km, double j2_coef)
    : name(std::move(name)), gm(gm), mean_radius_km(mean_radius_km), soi_radius_km(soi_radius_km), j2_coef(j2_coef)
{
    if (gm < 0) {
        throw std::invalid_argument("gm must be >= 0");
    }
    if (mean_radius_km < 0) {
        throw std::invalid_argument("mean_radius_km must be >= 0");
    }
    if (soi_radius_km < 0) {
        throw std::invalid_argument("soi_radius_km must be >= 0");
    }
    if (j2_coef < 0) {
        throw std::invalid_argument("j2_coef must be >= 0");
    }
}

std::string CelestialBody::getName() const {
    return name;
}

double CelestialBody::getGm() const {
    return gm;
}

double CelestialBody::getMeanRadius() const {
    return mean_radius_km;
}

double CelestialBody::getSoiRadius() const {
    return soi_radius_km;
}

double CelestialBody::getJ2Coef() const {
    return j2_coef;
}

const std::unordered_map<std::string, CelestialBody>& CelestialBody::catalogue() {
    static const std::unordered_map<std::string, CelestialBody> cat = {
        {"Sun", CelestialBody("Sun", 1.32712440018e11, 695700, 0, 0)},
        {"Mercury", CelestialBody("Mercury", 2.2032e4, 2439.7, 1.12e5, 6.0e-5)},
        {"Venus", CelestialBody("Venus", 3.24859e5, 6051.8, 6.16e5, 4.458e-6)},
        {"Earth", CelestialBody("Earth", 3.986004418e5, 6371.0, 9.25e5, 1.08263e-3)},
        {"Moon", CelestialBody("Moon", 4902.8, 1737.4, 6.61e4, 2.027e-4)},
        {"Mars", CelestialBody("Mars", 4.282837e4, 3389.5, 5.77e5, 1.9555e-3)},
        {"Jupiter", CelestialBody("Jupiter", 1.26686534e8, 69911.0, 4.82e7, 1.4736e-2)},
        {"Saturn", CelestialBody("Saturn", 3.7931187e7, 58232.0, 5.48e7, 1.6298e-2)},
        {"Uranus", CelestialBody("Uranus", 5.793987e6, 25362.0, 5.18e7, 3.343e-3)},
        {"Neptune", CelestialBody("Neptune", 6.836529e6, 24622.0, 8.66e7, 3.411e-3)},
    };
    return cat;
}

const CelestialBody& CelestialBody::get(const std::string& name) {
    const auto& cat = catalogue();
    const auto it = cat.find(name);
    if (it == cat.end())
        throw std::out_of_range("CelestialBody::get: unknown body '" + name + "'");
    return it->second;
}

bool CelestialBody::exists(const std::string& name) {
    return catalogue().count(name) > 0;
}