//
// Created by Connor Bethel on 09/05/2026.
//

#include <Orbit.h>
#include <OrbitalConverter.h>
#include <StateVector.h>

#include "RK4Integrator.h"
#include <gtest/gtest.h>

#include "Astrodynamics.h"

TEST(RK4Test, TestRK4Integration) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    Orbit iss(earth, 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0);
    StateVector initial_state = OrbitalConverter::toStateVector(iss, earth);

    auto derivative = [&](const StateVector& state) -> StateVector {
        Vec3 pos{state.getX(), state.getY(), state.getZ()};
        Vec3 acc = Astrodynamics::twoBodyAcceleration(pos, earth.getGm());
        return {state.getVX(), state.getVY(), state.getVZ(),
                           acc.x, acc.y, acc.z};
    };

    const double dt = 0.01;
    const int steps = static_cast<int>(std::round(iss.getPeriod() / dt));

    StateVector state = initial_state;
    for (int i = 0; i < steps; i++) {
        state = RK4Integrator::step(state, dt, derivative);
    }

    const Orbit final_orbit = OrbitalConverter::toOrbit(state, earth);
    EXPECT_NEAR(final_orbit.getSma(), iss.getSma(), 0.1);
    EXPECT_NEAR(final_orbit.getEcc(), iss.getEcc(), 1e-5);
    EXPECT_NEAR(final_orbit.getInc(), iss.getInc(), 0.001);

    EXPECT_NEAR(state.getX(), initial_state.getX(), 0.1);
    EXPECT_NEAR(state.getY(), initial_state.getY(), 0.1);
    EXPECT_NEAR(state.getZ(), initial_state.getZ(), 0.1);

    EXPECT_NEAR(state.getRadius(), initial_state.getRadius(), 1.0);
    EXPECT_NEAR(state.getSpeed(), initial_state.getSpeed(), 0.01);

    const double initial_energy = -earth.getGm() / (2.0 * iss.getSma());
    const double final_energy = 0.5 * state.getSpeed() * state.getSpeed()
                              - earth.getGm() / state.getRadius();

    EXPECT_NEAR(final_energy, initial_energy, std::abs(initial_energy) * 1e-6);
}