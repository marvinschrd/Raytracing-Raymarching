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

#include <omp.h>
#include <fstream>
#include  <chrono>

#include "raymarching.h"

namespace raytracing {
	
	float raymarching_clamp(float& rgb_value) {
		if (rgb_value > 255.0f) {
			rgb_value = 255.0f;
		}
		if (rgb_value < 0.0f) {
			rgb_value = 0.0f;
		}
		return rgb_value;
	}

	void RayMarcher::Render() {
	auto begin = std::chrono::high_resolution_clock::now();

	#pragma omp parallel for
		for (int i = 0; i < height_; ++i) {
			for (int j = 0; j < width_; ++j) {
				double dir_x = (j + 0.5f) - width_ / 2.0;
				double dir_y = -(i + 0.5f) + height_ / 2.0;
				double dir_z = -height_ / (2.0 * tan(fov_ / 2.0));

				maths::Vector3f ray_direction = maths::Vector3f(dir_x, dir_y, dir_z).Normalized();

				frame_buffer_[j + i * width_] = RayMarching(maths::Vector3f(0.0f, 0.0f, 0.0f),
					ray_direction);
			}
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
		std::cout << " raymarching duration : " << duration.count() << " microsecondes " << "\n";
		WriteImage();
	}

	void RayMarcher::WriteImage() {
		std::ofstream ofs("./ray_marching_image.ppm", std::ios::out | std::ios::binary);
		ofs << "P6\n" << width_ << " " << height_ << "\n255\n";
		for (uint32_t i = 0; i < height_ * width_; ++i) {
			char r = static_cast<char>(raymarching_clamp(frame_buffer_[i].x));
			char g = static_cast<char>(raymarching_clamp(frame_buffer_[i].y));
			char b = static_cast<char>(raymarching_clamp(frame_buffer_[i].z));

			ofs << r << g << b;
		}
		ofs.close();
	}

	bool RayMarcher::ShadowRay(
		const maths::Vector3f& hit_position,
		const maths::Vector3f& hit_normal,
		const maths::Vector3f& light_normal) {
		//Add a bias along the normal to prevent self collision
		const maths::Vector3f shadow_ray_origin(hit_position + hit_normal * bias_);
		maths::Ray3 shadow_ray(shadow_ray_origin, light_normal);
		Material tmp_material;
		HitInfos shadow_hit_info;

		float tmp_distance = ClosestDistance(shadow_ray, shadow_hit_info, tmp_material);
		if(tmp_distance != max_distance_) {
			return false;
		}
		
		// Return that the point is in the light
		return true;
	}

	maths::Vector3f RayMarcher::Reflect(
		const maths::Vector3f& ray_direction,
		const maths::Vector3f& hit_normal) {
		const float t = maths::Vector3f::Dot(ray_direction, hit_normal);

		const float r = 2.0f * t;

		return ray_direction - hit_normal * r;
	}

	float RayMarcher::ClosestDistance(maths::Ray3 ray, 
									  HitInfos& hit_infos, 
									  Material& hit_material) {
		float depth = min_distance_;
		maths::Sphere closest_sphere;

		for (int i = 0; i < max_marching_steps_; ++i) {
			maths::Vector3f p = ray.PointInRay(depth);
			float dist = SceneSDF(p, closest_sphere);

			if(dist < 0.0001f) {
				hit_material = closest_sphere.material();
				hit_infos.hit_position = p;
				hit_infos.normal = (p - closest_sphere.center()).Normalized();
				return depth;
			}

			depth += dist;
			if (depth >= max_distance_) {
				return max_distance_;
			}
		}
		return max_distance_;
	}

	maths::Vector3f RayMarcher::RayMarching(maths::Vector3f ray_origin, 
											maths::Vector3f ray_direction,
											const int& depth) {
		maths::Ray3 ray{ ray_origin,ray_direction };

		HitInfos hit_infos;
		Material hit_material;

		float distance = ClosestDistance(ray, hit_infos, hit_material);

		//didn't hit
		if (distance > max_distance_ - 0.0001f || depth >=4) {
			return background_color_;
		}

		//Compute the normal or direction of the light
		maths::Vector3f light_normal(light_.position - hit_infos.hit_position);
		light_normal.Normalize();


		// Calculate how much light is the point getting
		float light_value = maths::Vector3f::Dot(hit_infos.normal, light_normal);
		if (light_value < 0.0f) {
			light_value = 0.0f;
		}

		//Compute shadow ray to check if point is in shadow
		 bool in_light = ShadowRay(hit_infos.hit_position, hit_infos.normal, light_normal);


		 if(in_light) {
			 // Point is not in the shadow
				// Cast reflexion ray recursively to compute reflexion color
			 const maths::Vector3f reflection_direction = 
				 Reflect(ray_direction, hit_infos.normal).Normalized();

			 const maths::Vector3f reflection_origin(
				 hit_infos.hit_position + hit_infos.normal * bias_);

			 const maths::Vector3f reflection_color = 
				 RayMarching(reflection_origin, reflection_direction, depth + 1);

			 hit_material.set_color(hit_material.color() * light_value
				 += reflection_color * hit_material.reflexion_index());
		 }
		 else {
			 //Point is in the shadow
			 hit_material.set_color(hit_material.color() * light_value * in_light);
		 }
		 return hit_material.color();
	}

	float RayMarcher::SceneSDF(maths::Vector3f position, maths::Sphere& closest_sphere) {
		float dist = 100000.0f;

		for(int i = 0; i < spheres_.size(); ++i) {
			float distance = 0.0f;

			distance = spheres_[i].sdf(position);

			if(distance < dist) {
				dist = distance;
				closest_sphere = spheres_[i];
			}
		}
		return dist;
	}

}// namespace raytracing