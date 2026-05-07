//
// Created by Connor Bethel on 07/05/2026.
//

#include "Spacecraft.h"
#include <cmath>
#include <stdexcept>

constexpr double G0 = 9.80665; // m/s^2

Spacecraft::Spacecraft(const double dry_mass_kg, const double fuel_mass_kg, const double thrust_N, const double isp)
    : dry_mass_kg(dry_mass_kg), fuel_mass_kg(fuel_mass_kg), thrust_N(thrust_N), isp(isp)
{
    if (dry_mass_kg <= 0) {
        throw std::invalid_argument("dry_mass_kg cannot be <= 0");
    }
    if (fuel_mass_kg < 0) {
        throw std::invalid_argument("fuel_mass_kg cannot be < 0");
    }
    if (thrust_N <= 0) {
        throw std::invalid_argument("thrust_N cannot be <= 0");
    }
    if (isp <= 0) {
        throw std::invalid_argument("isp cannot be <= 0");
    }
}

double Spacecraft::getDryMass() const {
    return dry_mass_kg;
}

double Spacecraft::getFuelMass() const {
    return fuel_mass_kg;
}

double Spacecraft::getThrust() const {
    return thrust_N;
}

double Spacecraft::getIsp() const {
    return isp;
}

double Spacecraft::getWetMass() const {
    return dry_mass_kg + fuel_mass_kg;
}

double Spacecraft::getMaxDeltaV() const {
    const double max_delta_v = isp * G0 * std::log(getWetMass()/dry_mass_kg) / 1000; // returns m/s
    return max_delta_v;
}

double Spacecraft::getMassFlowRate() const {
    const double mass_flow_rate = thrust_N / (isp * G0);
    return mass_flow_rate;
}
