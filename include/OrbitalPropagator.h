//
// Created by Connor Bethel on 09/05/2026.
//

#ifndef ORBITALPROPAGATOR_H
#define ORBITALPROPAGATOR_H
#include <Orbit.h>

#include "Trajectory.h"


namespace OrbitalPropagator {
    Trajectory propagateOrbit(const Orbit& initial_orbit, double duration_s, double dt_s, double start_time_j2000_s);
};



#endif //ORBITALPROPAGATOR_H
