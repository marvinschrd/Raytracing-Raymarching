/*
MIT License

Copyright (c) 2021 SAE Institute Geneva

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "maths/vector3.h"
#include "maths/angle.h"

namespace maths {
/**
* \brief Class used to represent a 2D vector.
*/
class Vector2f {
public:

    union {
        struct {
            float x;
            float y;
        };

        float coord[2]{};
    };

    Vector2f() = default;

    Vector2f(const float x, const float y) : x(x), y(y) {
    }

    Vector2f operator+(Vector2f rhs) const;

    Vector2f& operator+=(Vector2f rhs);

    Vector2f operator-(Vector2f rhs) const;

    Vector2f& operator-=(Vector2f rhs);

    Vector2f operator*(float scalar) const;

    Vector2f& operator*=(float scalar);

    Vector2f operator/(float scalar) const;

    Vector2f& operator/=(float scalar);

    bool operator==(Vector2f rhs) const;

    bool operator!=(Vector2f rhs) const;

    const float operator[](size_t component) const;

    float& operator[](size_t component);

    float Magnitude() const;

    float SqrMagnitude() const;

    float Dot(Vector2f v2) const;

    static float Dot(Vector2f v1, Vector2f v2);

    Vector3f Cross(Vector2f v2) const;

    static Vector3f Cross(Vector2f v1, Vector2f v2);

    radian_t AngleBetween(Vector2f v2) const;

    static radian_t AngleBetween(Vector2f v1, Vector2f v2);

    Vector2f Normalized() const;

    void Normalize();

    Vector2f Lerp(Vector2f v2, float t) const;

    static Vector2f Lerp(Vector2f v1, Vector2f v2, float t);

    Vector2f Slerp(Vector2f v2, float t) const;

    Vector2f Rotation(radian_t angle) const;

    static Vector2f Rotation(Vector2f v1, radian_t angle);
};
} // namespace maths
