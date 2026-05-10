//
// Created by Connor Bethel on 09/05/2026.
//

#include <OrbitalConverter.h>

#include "OrbitalPropagator.h"
#include "Orbit.h"
#include "CelestialBody.h"
#include <gtest/gtest.h>

#include "Astrodynamics.h"
#include "Ephemeris.h"
#include "RK4Integrator.h"

TEST(PropagatorTest, ISSOneDay) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    Orbit iss(earth, 6771.0, 0.0006247, 51.6, 0.0, 0.0, 0.0);

    const double dt = 10.0;
    const double duration = 86400.0 * 1; // one day
    const double start_time = 0.0;   // J2000

    Trajectory traj = OrbitalPropagator::propagateOrbit(iss, duration, dt, start_time);

    // Trajectory should have roughly duration/dt + 1 points
    EXPECT_GT(traj.size(), 0);
    EXPECT_NEAR(traj.size(), duration / dt + 1, 5);

    // First point should match initial state
    EXPECT_NEAR(traj.front().getStateVec().getRadius(), iss.getPeriapsisRadius(), 10.0);

    // All points should have Earth as central body
    for (const auto& point : traj) {
        EXPECT_EQ(point.getBody().getName(), "Earth");
    }

    // Final orbital elements should be close to initial
    Orbit final_orbit = OrbitalConverter::toOrbit(traj.back().getStateVec(), earth);

    std::cout << "Initial RAAN: " << iss.getRaan() << std::endl;
    std::cout << "Final RAAN: " << final_orbit.getRaan() << std::endl;

    EXPECT_NEAR(final_orbit.getSma(), iss.getSma(), 10.0);
    EXPECT_NEAR(final_orbit.getInc(), iss.getInc(), 0.1);
}

TEST(PropagatorTest, EarthToSunSOI) {
    const CelestialBody& earth = CelestialBody::get("Earth");
    Orbit escape(earth, -13142.0, 1.5, 0.0, 0.0, 0.0, 0.0);

    const double dt = 10.0;
    const double duration = 200400;
    const double start_time = 0.0;

    Trajectory traj = OrbitalPropagator::propagateOrbit(escape, duration, dt, start_time);

    // Trajectory not empty
    EXPECT_GT(traj.size(), 0);

    // Starts in Earth's SOI
    EXPECT_EQ(traj.front().getBody().getName(), "Earth");

    // Ends in Sun's SOI
    EXPECT_EQ(traj.back().getBody().getName(), "Sun");

    // Find the transition point and verify it happened near Earth's SOI radius
    for (size_t i = 1; i < traj.size(); i++) {
        if (traj[i].getBody().getName() == "Sun" &&
            traj[i-1].getBody().getName() == "Earth") {
            double transition_radius = traj[i-1].getStateVec().getRadius();
            EXPECT_NEAR(transition_radius, earth.getSoiRadius(), 50.0);
            break;
            }
    }
}

TEST(PropagatorTest, SunToMarsSOI) {
    const CelestialBody& sun = CelestialBody::get("Sun");
    const CelestialBody& mars = CelestialBody::get("Mars");

    // Spacecraft just outside Mars's SOI at J2000, moving toward Mars
    StateVector initial_state(
        2.08041e8 - 580000.0,
        -2.00327e6,
        -5.15533e6,
        1.16456 + 5.0,
        26.2971,
        0.522248
    );

    Orbit initial_orbit = OrbitalConverter::toOrbit(initial_state, sun);
    Trajectory traj = OrbitalPropagator::propagateOrbit(initial_orbit, 50000.0, 10.0, 0.0);

    // Starts in heliocentric orbit
    EXPECT_EQ(traj.front().getBody().getName(), "Sun");

    // Verify transition into Mars's SOI occurred
    bool entered_mars = false;
    double transition_dist = 0.0;
    for (size_t i = 1; i < traj.size(); i++) {
        if (traj[i].getBody().getName() == "Mars" &&
            traj[i-1].getBody().getName() == "Sun") {
            entered_mars = true;

            // Verify transition happened near Mars SOI boundary
            StateVector mars_at_t = Ephemeris::getStateAt("Mars", traj[i-1].getTimestamp(), sun);
            double dx = traj[i-1].getStateVec().getX() - mars_at_t.getX();
            double dy = traj[i-1].getStateVec().getY() - mars_at_t.getY();
            double dz = traj[i-1].getStateVec().getZ() - mars_at_t.getZ();
            transition_dist = std::sqrt(dx*dx + dy*dy + dz*dz);
            break;
            }
    }

    EXPECT_TRUE(entered_mars);
    EXPECT_NEAR(transition_dist, mars.getSoiRadius(), 50.0);
}