//
// Created by Connor Bethel on 09/05/2026.
//

#ifndef TRAJECTORYPOINT_H
#define TRAJECTORYPOINT_H
#include "CelestialBody.h"
#include "StateVector.h"


class TrajectoryPoint {

public:
    TrajectoryPoint(const CelestialBody& body, double timestamp_s, const StateVector& state_vector);

    [[nodiscard]] const CelestialBody& getBody() const;
    [[nodiscard]] double getTimestamp() const;
    [[nodiscard]] const StateVector& getStateVec() const;

private:
    const CelestialBody& body;
    const double timestamp_s;
    const StateVector state_vector;
};



#endif //TRAJECTORYPOINT_H
