//
// Created by Connor Bethel on 09/05/2026.
//

#ifndef ASTRODYNAMICS_H
#define ASTRODYNAMICS_H
#include "CelestialBody.h"
#include "Vec3.h"

namespace Astrodynamics {
    // Return acceleration due to gravity
    inline Vec3 twoBodyAcceleration(const Vec3& position, double gm) {
        double pos_mag = magnitude(position);
        const Vec3 acceleration = position * (-gm/(pos_mag*pos_mag*pos_mag));
        return acceleration;
    }

    // Return acceleration due to the J2 Perturbation
    inline Vec3 j2Acceleration(const Vec3& position, const CelestialBody& body) {
        double pos_mag = magnitude(position);
        double mean_radius = body.getMeanRadius();
        double j2_coef = body.getJ2Coef();
        double gm = body.getGm();

        double r_pow_5 = pos_mag * pos_mag * pos_mag * pos_mag * pos_mag;
        double factor = (3.0/2.0) * (j2_coef * gm * (mean_radius * mean_radius)) / r_pow_5;

        double ax = factor * position.x * ((5.0 * position.z * position.z) / (pos_mag * pos_mag) - 1.0);
        double ay = factor * position.y * ((5.0 * position.z * position.z) / (pos_mag * pos_mag) - 1.0);
        double az = factor * position.z * ((5.0 * position.z * position.z) / (pos_mag * pos_mag) - 3.0);

        return {ax, ay, az};
    }
}

#endif //ASTRODYNAMICS_H
