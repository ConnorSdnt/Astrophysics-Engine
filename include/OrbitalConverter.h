//
// Created by Connor Bethel on 07/05/2026.
//

#ifndef ORBITALCONVERTER_H
#define ORBITALCONVERTER_H
#include "Orbit.h"
#include "StateVector.h"


namespace OrbitalConverter {
    StateVector toStateVector(const Orbit& orbit, const CelestialBody& body);
    Orbit toOrbit(const StateVector& state_vector, const CelestialBody& body);
};



#endif //ORBITALCONVERTER_H
