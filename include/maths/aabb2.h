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

#include "maths/vector2.h"

namespace maths {

// Class that creates an AABB2
class AABB2 {
public:
	AABB2() = default;
	AABB2(Vector2f bottom_left, Vector2f top_right) :
		bottom_left_(bottom_left), top_right_(top_right) {}
	Vector2f center() const {
		return { (bottom_left_ + top_right_) / 2.0f };
	}

	Vector2f extent() const {
		const Vector2f center_tmp = center();
		return { top_right_ - center_tmp };
	}

	Vector2f bottom_left() const { return bottom_left_; }
	Vector2f top_right() const { return top_right_; }
	
private:
	Vector2f bottom_left_ = {};
	Vector2f top_right_ = {};
};

// To find out if two AABBs are touching each other
bool Overlap(const AABB2& a, const AABB2& b);
// To find out if one AABB is contained in the other
bool Contain(const AABB2& a, const AABB2& b);
	
}  // namespace maths
