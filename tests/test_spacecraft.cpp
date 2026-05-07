//
// Created by Connor Bethel on 07/05/2026.
//
#include "Spacecraft.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(SpacecraftTest, ConstructsValidSpacecraft) {
    EXPECT_NO_THROW(Spacecraft(1000, 2000, 240000, 100));
}

TEST(SpacecraftTest, TestThrowsOnZeroDryMass) {
    EXPECT_THROW(Spacecraft(0, 2000, 240000, 100), std::invalid_argument);
}

TEST(SpacecraftTest, TestThrowsOnNegativeDryMass) {
    EXPECT_THROW(Spacecraft(-100, 2000, 240000, 100), std::invalid_argument);
}

TEST(SpacecraftTest, TestThrowsOnNegativeFuelMass) {
    EXPECT_THROW(Spacecraft(1000, -100, 10000, 300), std::invalid_argument);
}

TEST(SpacecraftTest, TestThrowsOnZeroFuelMass) {
    EXPECT_NO_THROW(Spacecraft(1000, 0, 10000, 300));
}

TEST(SpacecraftTest, TestGetWetMass) {
    const double dry_mass = 1000;
    const double fuel_mass = 1000;
    const double wet_mass = 2000;

    EXPECT_NEAR(Spacecraft(dry_mass, fuel_mass, 10000, 300).getWetMass(), wet_mass, 0.01);
}

TEST(SpacecraftTest, TestGetMaxDeltaV) {
    const double dry_mass = 1000;
    const double fuel_mass = 1000;
    const double wet_mass = 2000;
    const double isp = 300;
    const double g0 = 9.80665;
    const double thrust = 10000;

    const double max_delta_v = isp * g0 * std::log(wet_mass/dry_mass) / 1000;

    EXPECT_NEAR(Spacecraft(dry_mass, fuel_mass, thrust, isp).getMaxDeltaV(), max_delta_v, 0.01);
}

TEST(SpacecraftTest, TestGetMassFlowRate) {
    const double dry_mass = 1000;
    const double fuel_mass = 1000;
    const double isp = 300;
    const double g0 = 9.80665;
    const double thrust = 10000;

    const double mass_flow_rate = thrust / (isp * g0);

    EXPECT_NEAR(Spacecraft(dry_mass, fuel_mass, thrust, isp).getMassFlowRate(), mass_flow_rate, 0.01);
}

