//
// Created by Connor Bethel on 07/05/2026.
//
#include "OrbitalConverter.h"
#include "Orbit.h"
#include "StateVector.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(OrbitalConverterTest, TestISSOrbitToState) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit& ISS = Orbit(earth, 6771.0, 0.0006247, 51.6, 0, 0, 0);

    EXPECT_NEAR(OrbitalConverter::toStateVector(ISS, earth).getRadius(), 6766.77, 0.1);
    EXPECT_NEAR(OrbitalConverter::toStateVector(ISS, earth).getSpeed(), ISS.getSpeed(), 0.1);
}

TEST(OrbitalConverterTest, TestRoundTripConverter) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit& ISS = Orbit(earth, 6771.0, 0.0006247, 51.6, 0, 0, 0);
    const StateVector& state_from_first_orbit = OrbitalConverter::toStateVector(ISS, earth);
    const Orbit second_orbit_from_state = OrbitalConverter::toOrbit(state_from_first_orbit, earth);

    EXPECT_NEAR(second_orbit_from_state.getSma(), 6771.0, 0.1);
    EXPECT_NEAR(second_orbit_from_state.getEcc(), 0.0006247, 0.1);
    EXPECT_NEAR(second_orbit_from_state.getInc(), 51.6, 0.1);
    EXPECT_NEAR(second_orbit_from_state.getRaan(), 0, 0.1);
    EXPECT_NEAR(second_orbit_from_state.getAop(), 0, 0.1);
    EXPECT_NEAR(second_orbit_from_state.getAnom(), 0, 0.1);
}

TEST(OrbitalConverterTest, TestRoundTripNonZeroAngles) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit orbit(earth, 8000.0, 0.1, 45.0, 120.0, 60.0, 90.0);
    const StateVector state = OrbitalConverter::toStateVector(orbit, earth);
    const Orbit recovered = OrbitalConverter::toOrbit(state, earth);
    EXPECT_NEAR(recovered.getSma(),  8000.0, 0.1);
    EXPECT_NEAR(recovered.getEcc(),  0.1,    0.001);
    EXPECT_NEAR(recovered.getInc(),  45.0,   0.01);
    EXPECT_NEAR(recovered.getRaan(), 120.0,  0.01);
    EXPECT_NEAR(recovered.getAop(),  60.0,   0.01);
    EXPECT_NEAR(recovered.getAnom(), 90.0,   0.01);
}

TEST(OrbitalConverterTest, TestCircularOrbit) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit circular(earth, 6771.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    EXPECT_NO_THROW(OrbitalConverter::toStateVector(circular, earth));
    EXPECT_NEAR(OrbitalConverter::toStateVector(circular, earth).getRadius(), 6771.0, 0.1);
}

TEST(OrbitalConverterTest, TestHyperbolicOrbitRoundTrip) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit hyperbolic(earth, -10000.0, 1.5, 0.0, 0.0, 0.0, 0.0);
    const StateVector state = OrbitalConverter::toStateVector(hyperbolic, earth);
    const Orbit new_orbit = OrbitalConverter::toOrbit(state, earth);
    EXPECT_NEAR(new_orbit.getSma(),  -10000.0, 0.1);
    EXPECT_NEAR(new_orbit.getEcc(),  1.5,    0.001);
    EXPECT_NEAR(new_orbit.getInc(),  0.0,   0.01);
    EXPECT_NEAR(new_orbit.getRaan(), 0.0,  0.01);
    EXPECT_NEAR(new_orbit.getAop(),  0.0,   0.01);
    EXPECT_NEAR(new_orbit.getAnom(), 0.0,   0.01);
}

TEST(OrbitalConverterTest, TestHyperbolicOrbitRoundTripNonZeroAngles) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit hyperbolic(earth, -10000.0, 1.5, 45.0, 120.0, 60.0, 90.0);;
    const StateVector state = OrbitalConverter::toStateVector(hyperbolic, earth);
    const Orbit new_orbit = OrbitalConverter::toOrbit(state, earth);
    EXPECT_NEAR(new_orbit.getSma(),  -10000.0, 0.1);
    EXPECT_NEAR(new_orbit.getEcc(),  1.5,    0.001);
    EXPECT_NEAR(new_orbit.getInc(),  45.0,   0.01);
    EXPECT_NEAR(new_orbit.getRaan(), 120.0,  0.01);
    EXPECT_NEAR(new_orbit.getAop(),  60.0,   0.01);
    EXPECT_NEAR(new_orbit.getAnom(), 90.0,   0.01);
}

TEST(OrbitalConverterTest, TestCircularOrbitRoundTrip) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit circular(earth, 6771.0, 0.0, 28.5, 0.0, 0.0, 0.0);
    const StateVector state = OrbitalConverter::toStateVector(circular, earth);
    const Orbit recovered = OrbitalConverter::toOrbit(state, earth);
    EXPECT_NEAR(recovered.getSma(), 6771.0, 0.1);
    EXPECT_FALSE(std::isnan(recovered.getEcc()));
    EXPECT_FALSE(std::isnan(recovered.getInc()));
}

TEST(OrbitalConverterTest, TestCircularOrbitNonZeroAnom) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const Orbit circular(earth, 6771.0, 0.0, 28.5, 45.0, 30.0, 90.0);
    const StateVector state = OrbitalConverter::toStateVector(circular, earth);
    const Orbit recovered = OrbitalConverter::toOrbit(state, earth);
    EXPECT_NEAR(recovered.getSma(), 6771.0, 0.1);
    EXPECT_FALSE(std::isnan(recovered.getEcc()));
}