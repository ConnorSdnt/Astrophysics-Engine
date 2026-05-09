//
// Created by Connor Bethel on 07/05/2026.
//

#include "OrbitalConverter.h"
#include <cmath>
#include <algorithm>
#include "Vec3.h"
#include "Matrix3.h"
#include "OrbitalMath.h"

namespace OrbitalConverter {
    Matrix3 perifocalToInertial(double raan, double inc, double aop) {
        Matrix3 R{};

        R.m[0][0] = std::cos(raan)*std::cos(aop) - std::sin(raan)*std::sin(aop)*std::cos(inc);
        R.m[0][1] = -std::cos(raan)*std::sin(aop) - std::sin(raan)*std::cos(aop)*std::cos(inc);
        R.m[0][2] = std::sin(raan)*std::sin(inc);
        R.m[1][0] = std::sin(raan)*std::cos(aop) + std::cos(raan)*std::sin(aop)*std::cos(inc);
        R.m[1][1] = -std::sin(raan)*std::sin(aop) + std::cos(raan)*std::cos(aop)*std::cos(inc);
        R.m[1][2] = -std::cos(raan)*std::sin(inc);
        R.m[2][0] = std::sin(aop)*std::sin(inc);
        R.m[2][1] = std::cos(aop)*std::sin(inc);
        R.m[2][2] = std::cos(inc);

        return R;
    }

    StateVector toStateVector(const Orbit& orbit, const CelestialBody& body) {
        // Orbital elements
        const double sma = orbit.getSma();
        const double ecc = orbit.getEcc();
        const double anom_rad = orbit.getAnom() * (PI / 180.0);
        const double inc_rad  = orbit.getInc() * (PI / 180.0);
        const double raan_rad = orbit.getRaan() * (PI / 180.0);
        const double aop_rad = orbit.getAop() * (PI / 180.0);
        const double gm = body.getGm();

        // Current radius from centre of body
        const double r = sma * (1.0 - ecc*ecc) / (1.0 + ecc * std::cos(anom_rad));

        // Position in perifocal frame
        const double pos_x_peri = r * std::cos(anom_rad);
        const double pos_y_peri = r * std::sin(anom_rad);

        // Specific angular momentum
        const double h = std::sqrt(gm * std::abs(sma) * std::abs(1.0 - ecc*ecc));

        // Velocity in perifocal frame
        const double vel_x_peri = -(gm / h) * std::sin(anom_rad);
        const double vel_y_peri = (gm / h) * (ecc + std::cos(anom_rad));

        // Rotation matrix elements (perifocal → inertial)
        Matrix3 rotation = perifocalToInertial(
            raan_rad,
            inc_rad,
            aop_rad
        );

        Vec3 pos_peri {
            pos_x_peri,
            pos_y_peri,
            0.0
        };

        Vec3 vel_peri {
            vel_x_peri,
            vel_y_peri,
            0.0
        };

        Vec3 pos = rotation * pos_peri;
        Vec3 vel = rotation * vel_peri;

        return {pos.x, pos.y, pos.z, vel.x, vel.y, vel.z};
    }

    Orbit toOrbit(const StateVector& state_vector, const CelestialBody& body) {
        // Position and velocity components
        Vec3 pos {
            state_vector.getX(),
            state_vector.getY(),
            state_vector.getZ()
        };
        Vec3 vel {
            state_vector.getVX(),
            state_vector.getVY(),
            state_vector.getVZ()
        };
        const double gm = body.getGm();

        // Magnitudes
        const double r = magnitude(pos);
        const double v = magnitude(vel);

        // Angular momentum vector h = r × v
        Vec3 h_vec = cross(pos, vel);
        const double h = magnitude(h_vec);

        // Node vector n = [0,0,1] × h
        Vec3 n_vec {
            -h_vec.y,
             h_vec.x,
             0.0
        };
        const double n_mag = magnitude(n_vec);

        // Radial velocity (dot product of position and velocity)
        const double radial_vel = (pos.x*vel.x + pos.y*vel.y + pos.z*vel.z) / r;

        // Eccentricity vector e
        Vec3 e_vec = (
            (pos * (v*v - gm/r))
            - (vel * dot(pos, vel))
        ) * (1.0 / gm);
        const double ecc = magnitude(e_vec);

        // Semi-major axis from orbital energy
        const double orbital_energy = (v*v / 2.0) - (gm / r);
        const double sma = -gm / (2.0 * orbital_energy);

        // Inclination
        double inc_rad = safeAcos(h_vec.z / h);

        // RAAN with direction check
        double raan_rad = 0.0;

        if (n_mag > EPSILON) {
            raan_rad = std::atan2(n_vec.y, n_vec.x);
            if (raan_rad < 0) {
                raan_rad += 2.0 * PI;
            }
        }

        // Handle circular orbits
        if (ecc < EPSILON) {
            const double inc_deg  = inc_rad  * (180.0 / PI);
            const double raan_deg = raan_rad * (180.0 / PI);
            double anom_rad = 0.0;

            // Circular equatorial orbit
            if (n_mag < EPSILON) {
                anom_rad = std::atan2(pos.y, pos.x);
            }
            // Circular inclined orbit
            else {
                const double cos_u = (n_vec.x*pos.x + n_vec.y*pos.y) / (n_mag * r);
                const double sin_u = ((n_vec.x*(pos.y) - n_vec.y*(pos.x)) / (n_mag * r));
                anom_rad = std::atan2(sin_u, cos_u);
            }

            if (anom_rad < 0) {
                anom_rad += 2.0 * PI;
            }

            const double anom_deg = anom_rad * (180.0 / PI);

            return {body, sma, ecc, inc_deg, raan_deg, 0.0, anom_deg};
        }

        // Argument of periapsis with direction check
        double aop_rad = 0.0;
        if (n_mag > EPSILON && ecc > EPSILON) {
            double cos_arg = dot(n_vec, e_vec) / (n_mag * ecc);
            double sin_arg = dot(cross(n_vec, e_vec), h_vec) / (n_mag * ecc * h);
            aop_rad = std::atan2(sin_arg, cos_arg);

            if (aop_rad < 0) {
                aop_rad += 2.0 * PI;
            }
        }

        // True anomaly with direction check
        double anom_rad = 0.0;
        if (ecc > EPSILON) {
            double cos_true = dot(e_vec, pos) / (ecc * r);
            double sin_true = dot(cross(e_vec, pos), h_vec) / (ecc * h * r);
            anom_rad = std::atan2(sin_true, cos_true);

            if (anom_rad < 0) {
                anom_rad += 2.0 * PI;
            }
        }

        // Convert angles from radians to degrees
        const double inc_deg = toDegrees(inc_rad);
        const double raan_deg = toDegrees(raan_rad);
        const double aop_deg = toDegrees(aop_rad);
        const double anom_deg = toDegrees(anom_rad);

        return {body, sma, ecc, inc_deg, raan_deg, aop_deg, anom_deg};
    }

}