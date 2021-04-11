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

#include "maths/matrix3.h"
#include "maths/angle.h"
#include "maths/matrix2.h"
#include "maths/maths_utils.h"

namespace maths {
	
Matrix3f::Matrix3f(const Vector3f& v1, const Vector3f& v2, const Vector3f& v3) {
	
	matrix_[0] = v1;
	matrix_[1] = v2;
	matrix_[2] = v3;
}
Vector3f& Matrix3f::operator[](size_t index) {
	
	return matrix_[index];
}
const Vector3f& Matrix3f::operator[](size_t index) const {
	
	return matrix_[index];
}
Matrix3f Matrix3f::operator+(const Matrix3f& rhs) const {
	
	Matrix3f tmp_mat;

	for (int i = 0; i < matrix_.size(); i++) {

		for (int j = 0; j < matrix_.size(); j++) {

			tmp_mat[i][j] = matrix_[i][j] + rhs[i][j];
		}
	}

	return tmp_mat;
}
Matrix3f& Matrix3f::operator+=(const Matrix3f& rhs) {

	*this = *this + rhs;

	return *this;
}
Matrix3f Matrix3f::operator-(const Matrix3f& rhs) const {
	
	Matrix3f tmp_mat;

	for (int i = 0; i < matrix_.size(); i++) {

		for (int j = 0; j < matrix_.size(); j++) {

			tmp_mat[i][j] = matrix_[i][j] - rhs[i][j];
		}
	}

	return tmp_mat;
}
Matrix3f& Matrix3f::operator-=(const Matrix3f& rhs) {

	*this = *this - rhs;

	return *this;
}
Matrix3f Matrix3f::operator*(const Matrix3f& rhs) const {
	
	Matrix3f tmp_mat;

	for (int i = 0; i < matrix_.size(); i++) {

		for (int j = 0; j < matrix_.size(); j++) {

			for (int k = 0; k < matrix_.size(); k++) {

				tmp_mat[j][i] += matrix_[k][i] * rhs[j][k];
			}
		}
	}

	return tmp_mat;
}
Matrix3f& Matrix3f::operator*=(const Matrix3f& rhs) {
	
	*this = *this * rhs;

	return *this;
}
Vector3f Matrix3f::operator*(Vector3f rhs) const {
	
	Vector3f tmp_vec;

	tmp_vec.x = ((matrix_[0][0] * rhs.x) + (matrix_[1][0] * rhs.y) + (matrix_[2][0] * rhs.z));
	tmp_vec.y = ((matrix_[0][1] * rhs.x) + (matrix_[1][1] * rhs.y) + (matrix_[2][1] * rhs.z));
	tmp_vec.z = ((matrix_[0][2] * rhs.x) + (matrix_[1][2] * rhs.y) + (matrix_[2][2] * rhs.z));

	return tmp_vec;
}
Matrix3f& Matrix3f::operator*=(float scalar) {
	
	for (int i = 0; i < matrix_.size(); ++i) {
		
		for (int j = 0; j < matrix_.size(); ++j) {
			
			matrix_[i][j] *= scalar;
		}
	}

	return *this;
}
float Matrix3f::cofactor(int row, int column) const {
	
	const float kSign = (column + row) % 2 == 0 ? 1.0f : -1.0f;
	Matrix2f tmp_mat;
	int k = 0;
	int l = 0;

	//This double loop takes the elements of the 3x3 matrix necessary for the cofactor and copy them into the 2x2 tmp_mat
	for (int i = 0; i < matrix_.size(); ++i) {
		
		for (int j = 0; j < matrix_.size(); ++j) {
			
			if(i != column && j != row) {
				
				tmp_mat[k][l++] = matrix_[i][j];

				if(l == matrix_.size() -1) {
					
					l = 0;
					k++;
				}
			}
		}
	}

	const float kTmpDet = tmp_mat.determinant();
	
	return kSign * kTmpDet;
}
float Matrix3f::determinant() const {
	
	const float kDet = matrix_[0][0] * cofactor(0, 0)
					+ matrix_[0][1] * cofactor(1, 0)
					+ matrix_[0][2] * cofactor(2, 0);
	
	return kDet;
}
Matrix3f Matrix3f::Inverse() const {

	const float kDet = determinant();
	
	if(Equal(kDet, 0.0f)) {
		
		return *this;
	}

	if (IsOrthogonal()) {
		
		return Transpose();
	}

	Matrix3f tmp_mat = adjoint();

	tmp_mat *= (1.0f / kDet);

	return tmp_mat;
}
Matrix3f Matrix3f::Transpose() const {
	
	return Matrix3f(Vector3f(matrix_[0][0], matrix_[1][0], matrix_[2][0]),
					Vector3f(matrix_[0][1], matrix_[1][1], matrix_[2][1]),
					Vector3f(matrix_[0][2], matrix_[1][2], matrix_[2][2]));
}
Matrix3f Matrix3f::adjoint() const {
	
	Matrix3f tmp_mat;

	for (int i = 0; i < matrix_.size(); ++i) {
		
		for (int j = 0; j < matrix_.size(); ++j) {
			
			tmp_mat[i][j] = cofactor(j, i);
		}
	}
	
	return tmp_mat.Transpose();
}
bool Matrix3f::IsOrthogonal() const {
	
	return Equal(determinant(),1.0f);
}
Matrix3f Matrix3f::identity() {
	
	return Matrix3f(Vector3f(1, 0, 0), Vector3f(0, 1, 0), Vector3f(0, 0, 1));
}
Matrix3f Matrix3f::rotationMatrix(radian_t angle) {
	
	return Matrix3f(Vector3f(cos(angle), -sin(angle), 0),
					Vector3f(sin(angle), cos(angle), 0), 
					Vector3f(0, 0, 1)); 
}
Matrix3f Matrix3f::scalingMatrix(Vector2f axisValues) {
	
	return Matrix3f(Vector3f(axisValues.x, 0, 0), Vector3f(0, axisValues.y, 0), Vector3f(0, 0, 1));
}
Matrix3f Matrix3f::translationMatrix(Vector2f axisValues) {
	
	return Matrix3f(Vector3f(1, 0, axisValues.x), Vector3f(0, 1, axisValues.y), Vector3f(0, 0, 1));
}
	
}//namespace maths
