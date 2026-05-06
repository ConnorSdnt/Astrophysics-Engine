//
// Created by Connor Bethel on 07/05/2026.
//

#include "CelestialBody.h"
#include <gtest/gtest.h>

/*
 * Test the catalogue contains Earth, a valid body
 */
TEST(CelestialBodyTest, CheckEarthInCatalogue) {
    EXPECT_TRUE(CelestialBody::exists("Earth"));
}

/*
 * Test Earth is successfully retrieved from catalogue
 */
TEST(CelestialBodyTest, TestGetsValidBody) {
    EXPECT_NO_THROW(CelestialBody::get("Earth"));
}

/*
 * Test parameters of Earth can be retrieved
 */
TEST(CelestialBodyTest, TestGetNameOfEarth) {
    EXPECT_EQ(CelestialBody::get("Earth").getName(), "Earth");
}

/*
 * Test parameters of another planet (neptune) can be retrieved
 */
TEST(CelestialBodyTest, TestGetSoiOfNeptune) {
    EXPECT_EQ(CelestialBody::get("Neptune").getSoiRadius(), 8.66e7);
}

/*
 * Test throws on retrieval request of an invalid body
 */
TEST(CelestialBodyTest, ThrowsOnInvalidBody) {
    EXPECT_THROW(CelestialBody::get("demo"), std::out_of_range);
}
