//
// Created by Connor Bethel on 09/05/2026.
//

#include "TrajectoryPoint.h"

TrajectoryPoint::TrajectoryPoint(const CelestialBody &body, double timestamp_s, const StateVector &state_vector)
    : body(body), timestamp_s(timestamp_s), state_vector(state_vector)
{}

const CelestialBody &TrajectoryPoint::getBody() const {
    return body;
}

double TrajectoryPoint::getTimestamp() const {
    return timestamp_s;
}

const StateVector &TrajectoryPoint::getStateVec() const {
    return state_vector;
}




