#pragma once
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

#include "maths/circle.h"
#include "maths/aabb2.h"

namespace maths {

class Ray2 {
public:
    Ray2() = default;

    Ray2(Vector2f& origin, Vector2f& direction)
        : origin_(origin),
          direction_(direction) {
    }

    // Return a point along the ray from a given value
    Vector2f PointInRay(float value) const {
        return {origin_ + direction_ * value};
    }

    Vector2f origin() const { return origin_; }
    Vector2f direction() const { return direction_; }
    Vector2f unit_direction() const { return unit_direction_; }

    // Return true if ray intersect a circle
    bool IntersectCircle(const Circle& circle);
    //Return true if ray intersect AABB
    bool IntersectAABB2(const AABB2& aabb);

private:
    Vector2f origin_ = {};
    Vector2f direction_ = {};
    Vector2f unit_direction_ = direction_.Normalized();
    Vector2f hit_position_;
};

} // namespace maths
