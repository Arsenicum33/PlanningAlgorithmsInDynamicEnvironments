// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef PHYSICSUTILS_H
#define PHYSICSUTILS_H
#include <array>

namespace PhysicsUtils
{
    // Scalar multiplication (vector * scalar)
    inline std::array<double, 3> operator*(const std::array<double, 3>& vec, double scalar) {
        return { vec[0] * scalar, vec[1] * scalar, vec[2] * scalar };
    }

    // Scalar multiplication (scalar * vector)
    inline std::array<double, 3> operator*(double scalar, const std::array<double, 3>& vec) {
        return vec * scalar;
    }

    // Vector addition
    inline std::array<double, 3> operator+(const std::array<double, 3>& a, const std::array<double, 3>& b) {
        return { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
    }

    // Vector subtraction (if needed later)
    inline std::array<double, 3> operator-(const std::array<double, 3>& a, const std::array<double, 3>& b) {
        return { a[0] - b[0], a[1] - b[1], a[2] - b[2] };
    }

    // Dot product (optional, for future use)
    inline double dot(const std::array<double, 3>& a, const std::array<double, 3>& b) {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }

    inline double norm(const std::array<double, 3>& a) {
        return std::sqrt(dot(a, a));
    }

    inline std::array<double, 3> normalize(const std::array<double, 3>& a)
    {
        double normalizationConstant = sqrt(dot(a, a));
        if (normalizationConstant == 0)
            return std::array<double, 3>({ 0, 0, 0 });
        return std::array<double,3> { a[0] / normalizationConstant, a[1] / normalizationConstant , a[2]/normalizationConstant };
    }

    inline std::array<double, 3>& operator+=(std::array<double, 3>& a, const std::array<double, 3>& b) {
        a[0] += b[0];
        a[1] += b[1];
        a[2] += b[2];
        return a;
    }
}

#endif //PHYSICSUTILS_H
