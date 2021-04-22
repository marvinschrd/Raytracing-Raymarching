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
#include "maths/ray2.h"

namespace maths {

bool Ray2::IntersectCircle(const Circle& circle) {
    float distance;
    Vector2f v = circle.center() - origin();
    // Distance to closest point to sphere center
    float d = v.Dot(unit_direction_);

    if (d < 0) {
        return false;
    }

    // squared Distance between closest point to sphere center
    const float squaredDistance = v.Dot(v) - (d * d);
    const float radius2 = circle.radius() * circle.radius();
    if (squaredDistance > radius2) {
        return false;
    }

    const auto q = std::sqrt(radius2 - squaredDistance);

    const auto t0 = d + q;
    const auto t1 = d - q;

    bool hasHit = false;
    if (t0 >= 0) {
        distance = t0;
        hasHit = true;
    }

    if (t1 >= 0) {
        if (!hasHit || t1 < distance) {
            distance = t1;
            hasHit = true;
        }
    }

    if (!hasHit) {
        return false;
    }

    // calculate the position where the ray hit
    hit_position_ = origin() + unit_direction_ * distance;
    return true;
}

bool Ray2::IntersectAABB2(const AABB2& aabb) {
    const Vector2f lb = aabb.bottom_left();
    const Vector2f rt = aabb.top_right();
    Vector2f dirfrac;
    float distance;

    dirfrac.x = 1.0f / direction_.x;
    dirfrac.y = 1.0f / direction_.y;

    // lb is the corner of AABB with minimal coordinates - left bottom, rt is top right

    const float t1 = (lb.x - origin().x) * dirfrac.x;
    const float t2 = (rt.x - origin().x) * dirfrac.x;
    const float t3 = (lb.y - origin().y) * dirfrac.y;
    const float t4 = (rt.y - origin().y) * dirfrac.y;

    float tmin = std::max(std::min(t1, t2), std::min(t3, t4));
    float tmax = std::min(std::max(t1, t2), std::max(t3, t4));

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind
    if (tmax < 0) {
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax) {
        return false;
    }

    distance = tmin;
    // calculate the position where the ray hit
    hit_position_ = origin() + direction() * distance;
    return true;
}

} // namespace maths
