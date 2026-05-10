//
// Created by Connor Bethel on 09/05/2026.
//

#include "Orbit.h"
#include "OrbitalConverter.h"
#include "StateVector.h"

#include "Astrodynamics.h"
#include <gtest/gtest.h>

#include "Ephemeris.h"
#include "RK4Integrator.h"

TEST(AstrodynamicsTest, TestTwoBodyAcceleration) {
    Vec3 position = {7000, 0, 0};
    double gm = 398600.4418;
    EXPECT_NEAR(Astrodynamics::twoBodyAcceleration(position, gm).x, -0.008134, 0.0001);
    EXPECT_NEAR(Astrodynamics::twoBodyAcceleration(position, gm).y, 0.0, 1e-10);
    EXPECT_NEAR(Astrodynamics::twoBodyAcceleration(position, gm).z, 0.0, 1e-10);
}

TEST(AstrodynamicsTest, TestJ2Precession) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit initial_orbit = {earth, 6978.0, 0.001, 97.8, 0.0, 0.0, 0.0};
    const StateVector& initial_state = OrbitalConverter::toStateVector(initial_orbit, earth);

    auto derivative = [&](const StateVector& state) -> StateVector {
        Vec3 pos{state.getX(), state.getY(), state.getZ()};
        Vec3 acc = Astrodynamics::twoBodyAcceleration(pos, earth.getGm()) + Astrodynamics::j2Acceleration(pos, earth);
        return {state.getVX(), state.getVY(), state.getVZ(),
                           acc.x, acc.y, acc.z};
    };

    const double dt = 10.0;
    const int steps = 8640;

    StateVector state = initial_state;
    for (int i = 0; i < steps; i++) {
        state = RK4Integrator::step(state, dt, derivative);
    }

    const Orbit final_orbit = OrbitalConverter::toOrbit(state, earth);
    double raan_change = final_orbit.getRaan() - initial_orbit.getRaan();

    // Handle wrap-around
    if (raan_change < -180.0) raan_change += 360.0;
    if (raan_change >  180.0) raan_change -= 360.0;

    EXPECT_NEAR(raan_change, 0.9856, 0.01);
}

TEST(AstrodynamicsTest, TestNoJ2Precession) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit initial_orbit = {earth, 6978.0, 0.001, 97.8, 0.0, 0.0, 0.0};
    const StateVector& initial_state = OrbitalConverter::toStateVector(initial_orbit, earth);

    auto derivative = [&](const StateVector& state) -> StateVector {
        Vec3 pos{state.getX(), state.getY(), state.getZ()};
        Vec3 acc = Astrodynamics::twoBodyAcceleration(pos, earth.getGm());
        return {state.getVX(), state.getVY(), state.getVZ(),
                acc.x, acc.y, acc.z};
    };

    const double dt = 10.0;
    const int steps = 8640;

    StateVector state = initial_state;
    for (int i = 0; i < steps; i++) {
        state = RK4Integrator::step(state, dt, derivative);
    }

    const Orbit final_orbit = OrbitalConverter::toOrbit(state, earth);
    double raan_change = final_orbit.getRaan() - initial_orbit.getRaan();
    if (raan_change < -180.0) raan_change += 360.0;
    if (raan_change >  180.0) raan_change -= 360.0;
    EXPECT_NEAR(raan_change, 0.0, 0.01);
}

TEST(EphemerisTest, EarthStateInternallyConsistent) {
    const CelestialBody& sun = CelestialBody::get("Sun");
    StateVector earth = Ephemeris::getStateAt("Earth", 0.0, sun);

    // Verify vis-viva: v² = GM(2/r - 1/a)
    double r = earth.getRadius();
    double v = earth.getSpeed();
    double a = 1.00000261 * 149597870.7; // Earth SMA in km
    double gm = sun.getGm();

    double v_expected = std::sqrt(gm * (2.0/r - 1.0/a));
    EXPECT_NEAR(v, v_expected, 0.001); // within 1 m/s
}

TEST(EphemerisTest, EarthPositionAtJ2000MatchesHorizons) {
    const CelestialBody& sun = CelestialBody::get("Sun");
    StateVector earth = Ephemeris::getStateAt("Earth", 0.0, sun);
    // JPL Horizons reference values at J2000
    EXPECT_NEAR(earth.getX(), -26499033.68, 10000.0);
    EXPECT_NEAR(earth.getY(), 144697296.79, 10000.0);
    EXPECT_NEAR(earth.getZ(), -611.15,     1000.0);
    EXPECT_NEAR(earth.getVX(), -29.794, 0.5);
    EXPECT_NEAR(earth.getVY(), -5.469, 0.5);
    EXPECT_NEAR(earth.getVZ(), 0.000182, 0.01);
    EXPECT_NEAR(earth.getRadius(), 147103726.96, 10000.0);
}

TEST(EphemerisTest, EarthPositionAt2010MatchesHorizons) {
    const CelestialBody& sun = CelestialBody::get("Sun");
    StateVector earth = Ephemeris::getStateAt("Earth", 315619200.0, sun);

    // JPL Horizons reference values at J2000 + 10 years
    EXPECT_NEAR(earth.getX(), -2.761730272809177e+07, 50000.0);
    EXPECT_NEAR(earth.getY(),  1.444833783392449e+08, 50000.0);
    EXPECT_NEAR(earth.getZ(), -3211.65,               1000.0);
    EXPECT_NEAR(earth.getVX(), -29.731,                  0.5);
    EXPECT_NEAR(earth.getVY(),  -5.700,                  0.5);
    EXPECT_NEAR(earth.getVZ(),   0.00145,               0.01);
}

TEST(EphemerisTest, MarsPositionAt2010MatchesHorizons) {
    const CelestialBody& sun = CelestialBody::get("Sun");
    StateVector mars = Ephemeris::getStateAt("Mars", 0.0, sun);

    // JPL Horizons reference values at J2000 + 10 years
    EXPECT_NEAR(mars.getX(), 2.080481406418420E+08, 50000.0);
    EXPECT_NEAR(mars.getY(), -2.007052628025221E+06, 50000.0);
    EXPECT_NEAR(mars.getZ(), -5.156288959268022E+06, 1000.0);
    EXPECT_NEAR(mars.getVX(), 1.162672403766088E+00, 0.005);
    EXPECT_NEAR(mars.getVY(), 2.629606454546266E+01, 0.005);
    EXPECT_NEAR(mars.getVZ(), 5.222970229952857E-01, 0.0001);
}