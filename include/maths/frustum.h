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
#include <array>

#include "maths/matrix4.h"
#include "maths/sphere.h"
#include "maths/aabb3.h"
#include "maths/plane.h"

namespace maths {
	
class Frustum {
public:
	Frustum() = default;
	// Calculate frustum from the given informations from the camera each time it is called
	void calculate_frustum(Vector3f direction, Vector3f position, Vector3f right, 
		Vector3f up, float near_plane_distance, float far_plane_distance, 
		degree_t fov_x, radian_t fov_y);
	// Check if a sphere is inside the frustum
	bool contains(const Sphere& sphere);
	// Check if a AABB is inside the frustum
	bool contains(const AABB3& aabb);
	// Check if a point is inside the frustum
	bool contains(const Vector3f& point);
	
private:
	std::array<Plane, 6> planes_;
	enum Planes {NEAR, FAR, LEFT, RIGHT, TOP, BOTTOM};
};
	
} // namespace maths