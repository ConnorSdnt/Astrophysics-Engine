//
// Created by Connor Bethel on 09/05/2026.
//

#include "TrajectoryPoint.h"
#include <gtest/gtest.h>

TEST(TrajectoryPointTest, ConstructsValidPoint) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const StateVector state(1000.0, 2000.0, 3000.0, 1.0, 2.0, 3.0);
    EXPECT_NO_THROW(TrajectoryPoint(earth, 0.0, state));
}

TEST(TrajectoryPointTest, GettersReturnCorrectValues) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    const StateVector state(1000.0, 2000.0, 3000.0, 1.0, 2.0, 3.0);
    const TrajectoryPoint point(earth, 123.45, state);

    EXPECT_EQ(point.getBody().getName(), "Earth");
    EXPECT_DOUBLE_EQ(point.getTimestamp(), 123.45);
    EXPECT_DOUBLE_EQ(point.getStateVec().getX(), 1000.0);
}
