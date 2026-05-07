//
// Created by Connor Bethel on 07/05/2026.
//

#include "StateVector.h"
#include <gtest/gtest.h>

TEST(StateVectorTest, TestConstructsValidStateVector) {
    EXPECT_NO_THROW(StateVector(10, 10, 10, 10, 10, 10));
}

TEST(StateVectorTest, TestGetX) {
    EXPECT_EQ(StateVector(20, 10, 10, 10, 10, 10).getX(), 20);
}

TEST(StateVectorTest, TestGetY) {
    EXPECT_EQ(StateVector(10, 20, 10, 10, 10, 10).getY(), 20);
}

TEST(StateVectorTest, TestGetZ) {
    EXPECT_EQ(StateVector(10, 10, 20, 10, 10, 10).getZ(), 20);
}

TEST(StateVectorTest, TestGetVX) {
    EXPECT_EQ(StateVector(10, 10, 10, 20, 10, 10).getVX(), 20);
}

TEST(StateVectorTest, TestGetVY) {
    EXPECT_EQ(StateVector(10, 10, 10, 10, 20, 10).getVY(), 20);
}

TEST(StateVectorTest, TestGetVZ) {
    EXPECT_EQ(StateVector(10, 10, 10, 10, 10, 20).getVZ(), 20);
}

TEST(StateVectorTest, TestGetSpeed) {
    EXPECT_NEAR(StateVector(10, 10, 10, 20, 20, 20).getSpeed(), 34.641, 0.1);
}

TEST(StateVectorTest, TestGetRadius) {
    EXPECT_NEAR(StateVector(10, 10, 10, 20, 20, 20).getRadius(), 17.320, 0.1);
}

TEST(StateVectorTest, TestAddition) {
    StateVector a(1, 2, 3, 4, 5, 6);
    StateVector b(6, 5, 4, 3, 2, 1);
    StateVector result = a + b;
    EXPECT_NEAR(result.getX(), 7, 0.001);
    EXPECT_NEAR(result.getY(), 7, 0.001);
    EXPECT_NEAR(result.getZ(), 7, 0.001);
    EXPECT_NEAR(result.getVX(), 7, 0.001);
    EXPECT_NEAR(result.getVY(), 7, 0.001);
    EXPECT_NEAR(result.getVZ(), 7, 0.001);
}

TEST(StateVectorTest, TestScalarMultiplication) {
    StateVector a(1, 2, 3, 4, 5, 6);
    StateVector result = a * 2.0;
    EXPECT_NEAR(result.getX(), 2, 0.001);
    EXPECT_NEAR(result.getVZ(), 12, 0.001);
}

TEST(StateVectorTest, TestScalarMultiplicationCommutative) {
    StateVector a(1, 2, 3, 4, 5, 6);
    StateVector r1 = a * 3.0;
    StateVector r2 = 3.0 * a;
    EXPECT_NEAR(r1.getX(), r2.getX(), 0.001);
    EXPECT_NEAR(r1.getVZ(), r2.getVZ(), 0.001);
}