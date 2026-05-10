//
// Created by Connor Bethel on 09/05/2026.
//

#include "OrbitalPropagator.h"
#include "RK4Integrator.h"
#include "Astrodynamics.h"
#include "OrbitalConverter.h"
#include "CelestialBody.h"
#include "Ephemeris.h"
#include "StateVector.h"

namespace {
 // ==================
 // Internal Helpers
 // ==================

    const CelestialBody* detectSOI(const StateVector& state, const CelestialBody& current_body, double time_since_j2000) {

        Vec3 spacecraft_vec = {
            state.getX(),
            state.getY(),
            state.getZ()
        };

        // Check if spacecraft has exited current body's SOI
        if (current_body.hasParent()) {
            if (magnitude(spacecraft_vec) > current_body.getSoiRadius()) {
                return &CelestialBody::get(current_body.getParentName());
            }
        }

        // Check if spacecraft has entered any child body's SOI
        for (const auto& name : CelestialBody::getAllNames()) {
            const CelestialBody& candidate = CelestialBody::get(name);
            if (!candidate.hasParent()) continue;
            if (candidate.getParentName() != current_body.getName()) continue;
            if (!Ephemeris::hasEphemeris(name)) continue;

            StateVector candidate_pos = Ephemeris::getStateAt(name, time_since_j2000, current_body);
            Vec3 candidate_vec = {
                candidate_pos.getX(),
                candidate_pos.getY(),
                candidate_pos.getZ()
            };
            Vec3 diff = spacecraft_vec - candidate_vec;

            if (magnitude(diff) < candidate.getSoiRadius()) {
                return &candidate;
            }
        }
        return nullptr;
    }

    StateVector transitionFrame(const StateVector& state, const CelestialBody& old_body, const CelestialBody& new_body, double time_since_j2000) {

        if (old_body.getName() == "Sun") {
            // Sun has no ephemeris — get planet's state relative to Sun and negate
            const CelestialBody& sun = CelestialBody::get("Sun");
            StateVector planet_state = Ephemeris::getStateAt(new_body.getName(), time_since_j2000, sun);
            Vec3 new_pos = {
                state.getX() - planet_state.getX(),
                state.getY() - planet_state.getY(),
                state.getZ() - planet_state.getZ()
            };
            Vec3 new_vel = {
                state.getVX() - planet_state.getVX(),
                state.getVY() - planet_state.getVY(),
                state.getVZ() - planet_state.getVZ()
            };
            return {new_pos.x, new_pos.y, new_pos.z, new_vel.x, new_vel.y, new_vel.z};
        }

        StateVector old_body_state = Ephemeris::getStateAt(
            old_body.getName(),
            time_since_j2000,
            new_body
        );

        Vec3 new_pos = {
            state.getX() + old_body_state.getX(),
            state.getY() + old_body_state.getY(),
            state.getZ() + old_body_state.getZ()
        };
        Vec3 new_vel = {
            state.getVX() + old_body_state.getVX(),
            state.getVY() + old_body_state.getVY(),
            state.getVZ() + old_body_state.getVZ()
        };

        return {new_pos.x, new_pos.y, new_pos.z, new_vel.x, new_vel.y, new_vel.z};
    }

    void recordTrajectoryPoint(Trajectory& trajectory, const StateVector& state, double timestamp_s, const CelestialBody& body) {
        trajectory.emplace_back(body, timestamp_s, state);
    }
}

namespace OrbitalPropagator {
  Trajectory propagateOrbit(const Orbit &initial_orbit, double duration_s, double dt_s, double start_time_j2000_s) {

      Trajectory trajectory;

      const CelestialBody* current_body = &initial_orbit.getBody();
      double current_time = start_time_j2000_s;

      auto derivative = [&](const StateVector& state) -> StateVector {
          Vec3 pos{state.getX(), state.getY(), state.getZ()};
          Vec3 acc = Astrodynamics::twoBodyAcceleration(pos, current_body->getGm()) + Astrodynamics::j2Acceleration(pos, *current_body);
          return {state.getVX(), state.getVY(), state.getVZ(),
                             acc.x, acc.y, acc.z};
      };

      double duration = duration_s / dt_s;
      StateVector state = OrbitalConverter::toStateVector(initial_orbit, initial_orbit.getBody());

      recordTrajectoryPoint(trajectory, state, start_time_j2000_s, *current_body);

      for (int i = 0; i < duration; i++) {
          state = RK4Integrator::step(state, dt_s, derivative);
          current_time += dt_s;

          const CelestialBody* new_body = detectSOI(state, *current_body, current_time);
          if (new_body != nullptr) {
              state = transitionFrame(state, *current_body, *new_body, current_time);
              current_body = new_body;
          }

          recordTrajectoryPoint(trajectory, state, current_time, *current_body);
      }

      return trajectory;
  }
}