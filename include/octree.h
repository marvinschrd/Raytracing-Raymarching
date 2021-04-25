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
#include <vector>
#include <array>

#include "maths/sphere.h"
#include "maths/aabb3.h"
#include "maths/ray3.h"
#include "maths/contact3.h"

class Octree
{
public :
	Octree() = default;
	Octree(int max_sphere_number, int max_depth, maths::AABB3& AABB, int depth) : octree_aabb_(AABB), max_spheres_number_(max_sphere_number), max_depth_(max_depth), depth_(depth) {}

	void Insert(const maths::Sphere& sphere);

	void Split();

	std::vector<maths::Sphere> Retrieve_spheres( maths::Ray3 ray);

	bool has_split() const { return has_split_; }

	std::vector<maths::Sphere> spheres() const { return spheres_; }

	maths::AABB3 aabb() const { return octree_aabb_; }

	
private:
	maths::AABB3 octree_aabb_ = {};
	int depth_ = 1;
	int max_spheres_number_ = 3;
	int max_depth_ = 64;
	bool has_split_ = false;
	
	std::vector<Octree> childs_;
	std::vector<maths::Sphere> spheres_;
};