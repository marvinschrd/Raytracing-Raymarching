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

#include "maths/frustum.h"

namespace maths {
	
void Frustum::calculate_frustum(
		Vector3f direction, 
		Vector3f position, 
		Vector3f right, 
		Vector3f up, 
		float near_plane_distance, 
		float far_plane_distance, 
		degree_t fov_x, 
		radian_t fov_y)
{
	float near_plane_height = sin(fov_x / 2) * near_plane_distance * 2;
	float near_plane_width = sin(fov_y / 2) * near_plane_distance * 2;
	float far_plane_height = sin(fov_x / 2) * far_plane_distance * 2;
	float far_plane_width = sin(fov_y / 2) * far_plane_distance * 2;

	Vector3f direction1 = Vector3f{ (-1) * direction.x,
						  (-1) * direction.y, 
						  (-1) * direction.z };
		
	Vector3f near_point = direction1.Normalized() * near_plane_distance;
	Vector3f normal = direction1.Normalized();
	Vector3f normal2 = Vector3f{ (-1) * normal.x, 
					   (-1) * normal.y, 
					   (-1) * normal.z };

	Vector3f far_point = direction1.Normalized() * far_plane_distance;
	planes_[NEAR] = Plane{ near_point, normal };
	planes_[FAR] = Plane{ far_point, normal2};
		
	Vector3f ntr = planes_[0].point() + up * near_plane_height + 
				   right * near_plane_width;

	Vector3f nbr = planes_[0].point() - up * near_plane_height + 
				   right * near_plane_width;

	Vector3f nbl = planes_[0].point() - up * near_plane_height - 
				   right * near_plane_width;

	Vector3f ftr = planes_[1].point()+ up * far_plane_height + 
				   right * far_plane_width;

	Vector3f ftl = planes_[1].point() + up * far_plane_height - 
				   right * far_plane_width;

	Vector3f fbl = planes_[1].point()- up * far_plane_height - 
				   right * far_plane_width;

	planes_[RIGHT] = Plane{ ntr,nbr,ftr };
	planes_[LEFT] = Plane(ftl, fbl, nbl);
	planes_[TOP] = Plane(ntr, ftr, ftl);
	planes_[BOTTOM] = Plane(nbr, nbl, fbl);
}
bool Frustum::contains(const Sphere& sphere) {
	float distance;

	for (int i = 0; i < 6; i++) {
		distance = planes_[i].Distance(sphere.center());

		if (distance < -sphere.radius()) {
			return false;
		}
		else if (distance < sphere.radius()) {
			return true;
		}
	}
	return true;
}

bool Frustum::contains(const AABB3& aabb) {
	std::array<Vector3f, 8> aabbBounds;

	aabbBounds[0] = aabb.bottom_left();
	aabbBounds[1] = Vector3f(aabb.bottom_left().x, 
					aabb.bottom_left().y, 
					aabb.top_right().z);
	aabbBounds[2] = Vector3f(aabb.bottom_left().x, 
					aabb.top_right().y, 
					aabb.bottom_left().z);
	aabbBounds[3] = Vector3f(aabb.bottom_left().x, 
					aabb.top_right().y, 
					aabb.top_right().z);
	aabbBounds[4] = Vector3f(aabb.top_right().x, 
					aabb.bottom_left().y, 
					aabb.bottom_left().z);
	aabbBounds[5] = Vector3f(aabb.top_right().x, 
					aabb.bottom_left().y, 
					aabb.top_right().z);
	aabbBounds[6] = Vector3f(aabb.top_right().x, 
					aabb.top_right().y, 
					aabb.bottom_left().z);
	aabbBounds[7] = aabb.top_right();

	for (int i = 0; i < 6; i++) {
		float min = planes_[i].Distance(aabbBounds[0]);

		float max = min;

		for (int j = 1; j < 8; j++) {
			if (planes_[i].Distance(aabbBounds[j]) > max)
				max = planes_[i].Distance(aabbBounds[j]);
			if (planes_[i].Distance(aabbBounds[j]) < min)
				min = planes_[i].Distance(aabbBounds[j]);
		}
		if (max < 0.0f)
			return false;
	}
	return true;
}

bool Frustum::contains( const Vector3f& point)
{
	for (int i = 0; i < 6; i++) {
		if (planes_[i].Distance(point) < 0.0f) {
			return false;
		}
	}
	return true;
}

} // namespace maths