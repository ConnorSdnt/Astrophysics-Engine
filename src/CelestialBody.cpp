//
// Created by Connor Bethel on 06/05/2026.
//

#include "CelestialBody.h"
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <utility>

CelestialBody::CelestialBody(std::string  name, double gm, double mean_radius_km, double soi_radius_km, double j2_coef, std::string parent_name)
    : name(std::move(name)), gm(gm), mean_radius_km(mean_radius_km), soi_radius_km(soi_radius_km), j2_coef(j2_coef), parent_name(std::move(parent_name))
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

// Static functions
const CelestialBody& CelestialBody::get(const std::string& name) {
    const auto& cat = catalogue();
    const auto it = cat.find(name);
    if (it == cat.end())
        throw std::out_of_range("CelestialBody::get: unknown body '" + name + "'");
    return it->second;
}

const std::vector<std::string>& CelestialBody::getAllNames() {
    static const std::vector<std::string> names = {
        "Sun", "Mercury", "Venus", "Earth", "Moon", "Mars",
        "Jupiter", "Saturn", "Uranus", "Neptune"
    };
    return names;
}

// Getters

const std::string& CelestialBody::getName() const {
    return name;
}

const std::string& CelestialBody::getParentName() const {
    if (!hasParent())
        throw std::runtime_error("Body \'" + name + "\' has no parent");
    return parent_name;
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
        {"Sun", CelestialBody("Sun", 1.32712440018e11, 695700, 0, 0, "")},
        {"Mercury", CelestialBody("Mercury", 2.2032e4, 2439.7, 1.12e5, 6.0e-5, "Sun")},
        {"Venus", CelestialBody("Venus", 3.24859e5, 6051.8, 6.16e5, 4.458e-6, "Sun")},
        {"Earth", CelestialBody("Earth", 3.986004418e5, 6371.0, 9.25e5, 1.08263e-3, "Sun")},
        {"Moon", CelestialBody("Moon", 4902.8, 1737.4, 6.61e4, 2.027e-4, "Earth")},
        {"Mars", CelestialBody("Mars", 4.282837e4, 3389.5, 5.77e5, 1.9555e-3, "Sun")},
        {"Jupiter", CelestialBody("Jupiter", 1.26686534e8, 69911.0, 4.82e7, 1.4736e-2, "Sun")},
        {"Saturn", CelestialBody("Saturn", 3.7931187e7, 58232.0, 5.48e7, 1.6298e-2, "Sun")},
        {"Uranus", CelestialBody("Uranus", 5.793987e6, 25362.0, 5.18e7, 3.343e-3, "Sun")},
        {"Neptune", CelestialBody("Neptune", 6.836529e6, 24622.0, 8.66e7, 3.411e-3, "Sun")},
    };
    return cat;
}

bool CelestialBody::exists(const std::string& name) {
    return catalogue().count(name) > 0;
}

bool CelestialBody::hasParent() const {
    return !parent_name.empty();
}


