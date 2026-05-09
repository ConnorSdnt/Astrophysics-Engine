//
// Created by Connor Bethel on 09/05/2026.
//

#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vec3.h"

struct Matrix3 {
    double m[3][3];

    Vec3 operator*(const Vec3& v) const {
        return {
            m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
            m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
            m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
        };
    }
};

#endif //MATRIX3_H
