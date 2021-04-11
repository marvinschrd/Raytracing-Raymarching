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

#include "maths/matrix2.h"
#include "maths/maths_utils.h"

namespace maths {
	
Matrix2f::Matrix2f(const Vector2f& v1, const Vector2f& v2) {
	
	matrix_[0] = v1;
	matrix_[1] = v2;
}
Vector2f& Matrix2f::operator[](std::size_t index) {
	
	return matrix_[index];
}
const Vector2f& Matrix2f::operator[](std::size_t index) const {
	
	return matrix_[index];
}
Matrix2f Matrix2f::operator+(const Matrix2f& rhs) const {
	
	float m00 = matrix_[0][0] + rhs[0][0];
	float m01 = matrix_[0][1] + rhs[0][1];
	float m10 = matrix_[1][0] + rhs[1][0];
	float m11 = matrix_[1][1] + rhs[1][1];


	return Matrix2f(Vector2f(m00,m01),Vector2f(m10,m11));
}
Matrix2f& Matrix2f::operator+=(const Matrix2f& rhs) {
	
	*this = *this + rhs;

	return *this;
}
Matrix2f Matrix2f::operator-(const Matrix2f& rhs) const {
	
	float m00 = matrix_[0][0] - rhs[0][0];
	float m01 = matrix_[0][1] - rhs[0][1];
	float m10 = matrix_[1][0] - rhs[1][0];
	float m11 = matrix_[1][1] - rhs[1][1];
	
	return Matrix2f(Vector2f(m00, m01), Vector2f(m10, m11));
}
Matrix2f& Matrix2f::operator-=(const Matrix2f& rhs) {
	
	*this = *this - rhs;

	return *this;
}
Matrix2f Matrix2f::operator*(const Matrix2f& rhs) const {
	
	float m00 = (matrix_[0][0] * rhs[0][0]) + (matrix_[1][0] * rhs[0][1]);
	float m01 = (matrix_[0][1] * rhs[0][0]) + (matrix_[1][1] * rhs[0][1]);
	float m10 = (matrix_[0][0] * rhs[1][0]) + (matrix_[1][0] * rhs[1][1]);
	float m11 = (matrix_[0][1] * rhs[1][0]) + (matrix_[1][1] * rhs[1][1]);

	
	return Matrix2f(Vector2f(m00, m01), Vector2f(m10, m11));
}
Matrix2f& Matrix2f::operator*=(const Matrix2f& rhs) {
	
	*this = *this * rhs;

	return *this;
}
Matrix2f& Matrix2f::operator*=(float scalar) {
	
	matrix_[0][0] *= scalar;
	matrix_[0][1] *= scalar;
	matrix_[1][0] *= scalar;
	matrix_[1][1] *= scalar;

	return *this;
}
Vector2f Matrix2f::operator*(Vector2f rhs) const {
	
	Vector2f tmp_vec;

	tmp_vec.x = ((matrix_[0][0] * rhs.x) + (matrix_[1][0] * rhs.y));
	tmp_vec.y = ((matrix_[0][1] * rhs.x) + (matrix_[1][1] * rhs.y));

	return tmp_vec;
}
float Matrix2f::determinant() const {
	
	return (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
}
Matrix2f Matrix2f::Inverse() const {
	
	Matrix2f inverse;
	
	inverse[0][0] = matrix_[1][1];
	inverse[0][1] = -matrix_[1][0];
	inverse[1][0] = -matrix_[0][1];
	inverse[1][1] = matrix_[0][0];

	inverse *= 1/determinant();
	
	return inverse;
}
Matrix2f Matrix2f::Transpose() const {
	
	return Matrix2f(Vector2f(matrix_[0][0], matrix_[1][0]), Vector2f(matrix_[0][1], matrix_[1][1]));
}
bool Matrix2f::IsOrthogonal() const {

	return Equal(determinant(), 1.0f);
}
Matrix2f Matrix2f::identity() {
	
	return Matrix2f(Vector2f(1, 0), Vector2f(0, 1));
}
	
}//namespace maths
