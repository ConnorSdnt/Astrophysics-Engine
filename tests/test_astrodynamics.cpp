//
// Created by Connor Bethel on 09/05/2026.
//

#include "Orbit.h"
#include "OrbitalConverter.h"
#include "StateVector.h"

#include "Astrodynamics.h"
#include <gtest/gtest.h>
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