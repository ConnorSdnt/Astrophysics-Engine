//
// Created by Connor Bethel on 09/05/2026.
//

#ifndef EPHEMERIS_H
#define EPHEMERIS_H
#include "CelestialBody.h"
#include <unordered_map>
#include "StateVector.h"


class Ephemeris {
public:
    static const Ephemeris& get(const std::string& name);
    static const Ephemeris& get(const char* name) { return get(std::string(name)); }
    static StateVector getStateAt(const std::string& body_name, double seconds_since_j2000, const CelestialBody& parent_body);
    static bool hasEphemeris(const std::string& body_name);

private:
    Ephemeris(
        double sma_au, double ecc, double inc_deg,
        double mean_longitude_deg, double long_perihelion_deg, double raan_deg,
        double sma_rate_au, double ecc_rate, double inc_rate_deg,
        double mean_longitude_rate_deg, double long_perihelion_rate_deg,
        double raan_rate_deg
    );

    static const std::unordered_map<std::string, Ephemeris>& catalogue();

    const double sma_au;
    const double ecc;
    const double inc_deg;
    const double mean_longitude_deg;
    const double long_perihelion_deg;
    const double raan_deg;

    const double sma_rate_au;
    const double ecc_rate;
    const double inc_rate_deg;
    const double mean_longitude_rate_deg;
    const double long_perihelion_rate_deg;
    const double raan_rate_deg;
};



#endif //EPHEMERIS_H
