#include "Ephemeris.h"
#include "Orbit.h"
#include "OrbitalConverter.h"
#include "OrbitalMath.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

Ephemeris::Ephemeris(
    double sma_au, double ecc, double inc_deg,
    double mean_longitude_deg, double long_perihelion_deg, double raan_deg,
    double sma_rate_au, double ecc_rate, double inc_rate_deg,
    double mean_longitude_rate_deg, double long_perihelion_rate_deg, double raan_rate_deg)
    : sma_au(sma_au), ecc(ecc), inc_deg(inc_deg),
      mean_longitude_deg(mean_longitude_deg), long_perihelion_deg(long_perihelion_deg),
      raan_deg(raan_deg), sma_rate_au(sma_rate_au), ecc_rate(ecc_rate),
      inc_rate_deg(inc_rate_deg), mean_longitude_rate_deg(mean_longitude_rate_deg),
      long_perihelion_rate_deg(long_perihelion_rate_deg), raan_rate_deg(raan_rate_deg)
{}

const std::unordered_map<std::string, Ephemeris>& Ephemeris::catalogue() {
    static const std::unordered_map<std::string, Ephemeris> cat = {
        {"Mercury", Ephemeris(0.38709927,  0.20563593,  7.00497902,  252.25032350,  77.45779628,  48.33076593,
                              0.00000037,  0.00001906, -0.00594749, 149472.67411175,  0.16047689,  -0.12534081)},
        {"Venus",   Ephemeris(0.72333566,  0.00677672,  3.39467605,  181.97909950, 131.60246718,  76.67984255,
                              0.00000390, -0.00004107, -0.00078890,  58517.81538729,  0.00268329,  -0.27769418)},
        {"Earth",   Ephemeris(1.00000261,  0.01671123, -0.00001531,  100.46457166, 102.93768193,   0.0,
                              0.00000562, -0.00004392, -0.01294668,  35999.37244981,  0.32327364,   0.0)},
        {"Mars",    Ephemeris(1.52371034,  0.09339410,  1.84969142,   -4.55343205, -23.94362959,  49.55953891,
                              0.00001847,  0.00007882, -0.00813131,  19140.30268499,  0.44441088,  -0.29257343)},
        {"Jupiter", Ephemeris(5.20288700,  0.04838624,  1.30439695,   34.39644051,  14.72847983, 100.47390909,
                             -0.00011607, -0.00013253, -0.00183714,   3034.74612775,  0.21252668,   0.20469106)},
        {"Saturn",  Ephemeris(9.53667594,  0.05386179,  2.48599187,   49.95424423,  92.59887831, 113.66242448,
                             -0.00125060, -0.00050991,  0.00193609,   1222.49309132, -0.41897216,  -0.28867794)},
        {"Uranus",  Ephemeris(19.18916464, 0.04725744,  0.77263783,  313.23810451, 170.95427630,  74.01692503,
                             -0.00196176, -0.00004397, -0.00242939,    428.48202785,  0.40805281,   0.04240589)},
        {"Neptune", Ephemeris(30.06992276, 0.00859048,  1.77004347,  -55.12002969,  44.96476227, 131.78422574,
                              0.00026291,  0.00005105,  0.00035372,    218.45945325, -0.32241464,  -0.00508664)},
    };
    return cat;
}

const Ephemeris& Ephemeris::get(const std::string& name) {
    const auto& cat = catalogue();
    const auto it = cat.find(name);
    if (it == cat.end())
        throw std::out_of_range("Ephemeris::get: unknown body '" + name + "'");
    return it->second;
}

bool Ephemeris::hasEphemeris(const std::string& body_name) {
    return catalogue().count(body_name) > 0;
}

StateVector Ephemeris::getStateAt(const std::string& body_name, double seconds_since_j2000, const CelestialBody& parent_body) {
    const Ephemeris& eph = get(body_name);

    // Centuries since J2000
    const double centuries = seconds_since_j2000 / (36525.0 * 86400.0);

    // Apply rates to get current elements
    double sma = eph.sma_au + eph.sma_rate_au * centuries;
    double ecc = eph.ecc + eph.ecc_rate * centuries;
    double inc = eph.inc_deg + eph.inc_rate_deg * centuries;
    double L = eph.mean_longitude_deg + eph.mean_longitude_rate_deg  * centuries;
    double lp = eph.long_perihelion_deg + eph.long_perihelion_rate_deg * centuries;
    double raan = eph.raan_deg + eph.raan_rate_deg * centuries;

    // Derive standard elements
    double aop = lp - raan;
    double mean_anomaly = L - lp;

    // Normalise angles to [0, 360)
    auto normalise = [](double deg) {
        deg = std::fmod(deg, 360.0);
        if (deg < 0.0) deg += 360.0;
        return deg;
    };

    raan = normalise(raan);
    aop = normalise(aop);
    mean_anomaly = normalise(mean_anomaly);

    // Solve Kepler's equation for eccentric anomaly (Newton-Raphson)
    double M = mean_anomaly * (PI / 180.0); // radians
    double E = M;
    for (int i = 0; i < 100; i++) {
        double dE = (M - E + ecc * std::sin(E)) / (1.0 - ecc * std::cos(E));
        E += dE;
        if (std::abs(dE) < 1e-10) break;
    }

    // Eccentric anomaly to true anomaly
    double true_anomaly = 2.0 * std::atan2(
        std::sqrt(1.0 + ecc) * std::sin(E / 2.0),
        std::sqrt(1.0 - ecc) * std::cos(E / 2.0)
    );
    double true_anomaly_deg = normalise(true_anomaly * (180.0 / PI));

    // Convert AU to km
    const double AU_TO_KM = 149597870.7;
    double sma_km = sma * AU_TO_KM;

    // Construct orbit and convert to state vector
    Orbit orbit(parent_body, sma_km, ecc, inc, raan, aop, true_anomaly_deg);
    return OrbitalConverter::toStateVector(orbit, parent_body);;
}