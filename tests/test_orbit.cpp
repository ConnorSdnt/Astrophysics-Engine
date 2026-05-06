//
// Created by Connor Bethel on 06/05/2026.
//

#include "Orbit.h"
#include <gtest/gtest.h>

/*
 * Test constructor works for a valid orbit
 */
TEST(OrbitTest, ConstructsValidOrbit) {
    EXPECT_NO_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418));
}

/*
 * Test constructor throws an error on negative semi major axis
 */
TEST(OrbitTest, ThrowsOnNegativeSma) {
    EXPECT_THROW(Orbit("Earth", -6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418),
                 std::invalid_argument);
}

/*
 * Test constructor throws an error on negative eccentricity
 */
TEST(OrbitTest, ThrowsOnNegativeEcc) {
    EXPECT_THROW(Orbit("Earth", 6771.0, -0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418),
                 std::invalid_argument);
}

/*
 * Test constructor throws an error on negative inclination
 */
TEST(OrbitTest, ThrowsOnNegativeInc) {
    EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, -51.6, 0.0, 0.0, 0.0, 398600.4418),
                 std::invalid_argument);
}

/*
 * Test constructor throws an error on negative raan
 */
TEST(OrbitTest, ThrowsOnNegativeRaan) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, -1.0, 0.0, 0.0, 398600.4418),
              std::invalid_argument);
}

/*
 * Test constructor throws an error on negative aop
 */
TEST(OrbitTest, ThrowsOnNegativeAop) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, 0.0, -1.0, 0.0, 398600.4418),
              std::invalid_argument);
}

/*
 * Test constructor throws an error on negative anom
 */
TEST(OrbitTest, ThrowsOnNegativeAnom) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, -1.0, 398600.4418),
              std::invalid_argument);
}

/*
 * Test constructor throws an error on negative gm
 */
TEST(OrbitTest, ThrowsOnNegativeGm) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, -398600.4418),
              std::invalid_argument);
}

/*
 * Test constructor throws an error on upper bound of Inc
 */
TEST(OrbitTest, ThrowsOnIncOver180) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 181.0, 0.0, 0.0, 0.0, 398600.4418),
              std::invalid_argument);
}

/*
 * Test constructor throws an error on upper bound of raan
 */
TEST(OrbitTest, ThrowsOnRaanOver360) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, 361.0, 0.0, 0.0, 398600.4418),
              std::invalid_argument);
}

/*
 * Test constructor throws an error on upper bound of aop
 */
TEST(OrbitTest, ThrowsOnAopOver360) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, 0.0, 361.0, 0.0, 398600.4418),
              std::invalid_argument);
}

/*
 * Test constructor throws an error on upper bound of anom
 */
TEST(OrbitTest, ThrowsOnAnomOver360) {
 EXPECT_THROW(Orbit("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 361.0, 398600.4418),
              std::invalid_argument);
}

/*
 * Test that the correct period is returned for ISS parameters
 */
TEST(OrbitTest, ISSPeriod) {
 Orbit iss("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418);
 EXPECT_NEAR(iss.getPeriod(), 5554.0, 30.0);
}

/*
 * Test that the correct speed is returned for ISS parameters
 */
TEST(OrbitTest, ISSSpeed) {
 Orbit iss("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418);
 EXPECT_NEAR(iss.getSpeed(), 7.66, 0.05);
}

/*
 * Test that the correct periapsis is returned for ISS parameters
 */
TEST(OrbitTest, ISSPeriapsisRadius) {
 Orbit iss("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418);
 EXPECT_NEAR(iss.getPeriapsisRadius(), 6766.77, 0.1);
}

/*
 * Test that the correct apoapsis is returned for ISS parameters
 */
TEST(OrbitTest, ISSApoapsisRadius) {
 Orbit iss("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418);
 EXPECT_NEAR(iss.getApoapsisRadius(), 6775.23, 0.1);
}

/*
 * Test that the correct radius is returned for ISS parameters
 */
TEST(OrbitTest, ISSRadius) {
 Orbit iss("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418);
 EXPECT_NEAR(iss.getRadius(), 6766.77, 0.1);
}

/*
 * Test that the correct specific orbital energy is returned for ISS parameters
 */
TEST(OrbitTest, ISSSpecificOrbitalEnergy) {
 Orbit iss("Earth", 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0, 398600.4418);
 EXPECT_NEAR(iss.getSpecificOrbitalEnergy(), -29.43, 0.1);
}