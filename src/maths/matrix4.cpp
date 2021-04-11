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
#include "maths/matrix4.h"
#include "maths/maths_utils.h"


namespace maths
{
Matrix4f::Matrix4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& v4) {
	
	matrix_[0] = v1;
	matrix_[1] = v2;
	matrix_[2] = v3;
	matrix_[3] = v4;
}
Vector4f& Matrix4f::operator[](std::size_t index) {
	
	return matrix_[index];
}
const Vector4f& Matrix4f::operator[](std::size_t index) const {
	
	return matrix_[index];
}
Matrix4f Matrix4f::operator+(const Matrix4f& rhs) const {
	
	Matrix4f tmp_mat;

	for (int i = 0; i < matrix_.size(); i++) {

		for (int j = 0; j < matrix_.size(); j++) {

			tmp_mat[i][j] = matrix_[i][j] + rhs[i][j];
		}
	}

	return tmp_mat;
}
Matrix4f& Matrix4f::operator+=(const Matrix4f& rhs) {
	
	*this = *this + rhs;

	return *this;
}
Matrix4f Matrix4f::operator-(const Matrix4f& rhs) const {
	
	Matrix4f tmp_mat;

	for (int i = 0; i < matrix_.size(); i++) {

		for (int j = 0; j < matrix_.size(); j++) {

			tmp_mat[i][j] = matrix_[i][j] - rhs[i][j];
		}
	}

	return tmp_mat;
}
Matrix4f& Matrix4f::operator-=(const Matrix4f& rhs) {
	
	*this = *this - rhs;

	return *this;
}
Matrix4f Matrix4f::operator*(const Matrix4f& rhs) const {
	
	Matrix4f tmp_mat;

	for (int i = 0; i < matrix_.size(); i++) {

		for (int j = 0; j < matrix_.size(); j++) {

			for (int k = 0; k < matrix_.size(); k++) {

				tmp_mat[j][i] += matrix_[k][i] * rhs[j][k];
			}
		}
	}

	return tmp_mat;
}
Matrix4f& Matrix4f::operator*=(const Matrix4f& rhs) {
	
	*this = *this * rhs;

	return *this;
}
Vector4f Matrix4f::operator*(Vector4f rhs) const {
	
	Vector4f tmp_vec;

	tmp_vec.x = ((matrix_[0][0] * rhs.x) + (matrix_[1][0] * rhs.y) + (matrix_[2][0] * rhs.z) + (matrix_[3][0] * rhs.w));
	tmp_vec.y = ((matrix_[0][1] * rhs.x) + (matrix_[1][1] * rhs.y) + (matrix_[2][1] * rhs.z) + (matrix_[3][1] * rhs.w));
	tmp_vec.z = ((matrix_[0][2] * rhs.x) + (matrix_[1][2] * rhs.y) + (matrix_[2][2] * rhs.z) + (matrix_[3][2] * rhs.w));
	tmp_vec.w = ((matrix_[0][3] * rhs.x) + (matrix_[1][3] * rhs.y) + (matrix_[2][3] * rhs.z) + (matrix_[3][3] * rhs.w));

	return tmp_vec;
}
Matrix4f& Matrix4f::operator*=(float scalar) {
	
	for (int i = 0; i < matrix_.size(); ++i) {
		
		for (int j = 0; j < matrix_.size(); ++j) {
			
			matrix_[i][j] *= scalar;
		}
	}

	return *this;
}
float Matrix4f::cofactor(int row, int column) const {
	
	const float kSign = (column + row) % 2 == 0 ? 1.0f : -1.0f;
	Matrix3f tmp_mat;
	int k = 0;
	int l = 0;

	//This double loop takes the elements of the 3x3 matrix necessary for the cofactor and copy them into the 2x2 tmp_mat
	for (int i = 0; i < matrix_.size(); ++i) {
		
		for (int j = 0; j < matrix_.size(); ++j) {
			
			if (i != column && j != row) {
				
				tmp_mat[k][l++] = matrix_[i][j];

				if (l == matrix_.size() - 1) {
					
					l = 0;
					k++;
				}
			}
		}
	}

	const float kTmpDet = tmp_mat.determinant();

	return kSign * kTmpDet;
}
float Matrix4f::determinant() const {
	
	const float kDet = matrix_[0][0] * cofactor(0, 0)
					+ matrix_[0][1] * cofactor(1, 0)
					+ matrix_[0][2] * cofactor(2, 0)
					+ matrix_[0][3] * cofactor(3, 0);

	return kDet;
}
Matrix4f Matrix4f::Inverse() const {

	const float kDet = determinant();
	
	if(Equal(kDet, 0.0f)) {
		
		return *this;
	}
	
	if (IsOrthogonal()) {
		
		return Transpose();
	}
	
	Matrix4f tmp_mat = adjoint();

	tmp_mat *= (1.0f / determinant());

	return tmp_mat;
}
Matrix4f Matrix4f::Transpose() const {
	
	return Matrix4f(Vector4f(matrix_[0][0], matrix_[1][0], matrix_[2][0], matrix_[3][0]),
					Vector4f(matrix_[0][1], matrix_[1][1], matrix_[2][1], matrix_[3][1]),
					Vector4f(matrix_[0][2], matrix_[1][2], matrix_[2][2], matrix_[3][2]),
					Vector4f(matrix_[0][3], matrix_[1][3], matrix_[2][3], matrix_[3][3]));
}
Matrix4f Matrix4f::adjoint() const {
	
	Matrix4f tmp_mat;

	for (int i = 0; i < matrix_.size(); ++i) {
		
		for (int j = 0; j < matrix_.size(); ++j) {
			
			tmp_mat[i][j] = cofactor(j, i);
		}
	}

	return tmp_mat.Transpose();
}
bool Matrix4f::IsOrthogonal() const {
	
	return Equal(determinant(), 1.0f);
}
Matrix4f Matrix4f::identity() {
	
	return Matrix4f(Vector4f(1, 0, 0, 0), 
					Vector4f(0, 1, 0, 0), 
					Vector4f(0, 0, 1, 0), 
					Vector4f(0, 0, 0, 1));
}
Matrix4f Matrix4f::rotationMatrix(radian_t angle, char axis) {
	
	if(axis != 'x' && axis != 'y' && axis != 'z') {
		
		return Matrix4f(Vector4f(0, 0, 0, 0),
						Vector4f(0, 0, 0, 0),
						Vector4f(0, 0, 0, 0),
						Vector4f(0, 0, 0, 0));
	}
	
	switch(axis) {
		
	case 'x': {
			
			return Matrix4f(Vector4f(0, cos(angle), -sin(angle), 0),
							Vector4f(0, sin(angle), cos(angle), 0),
							Vector4f(0, 1, 0, 0),
							Vector4f(0, 0, 0, 1));
			break;
		}
		
	case 'y': {
			
			return Matrix4f(Vector4f(-sin(angle), 0, cos(angle), 0),
							Vector4f(cos(angle), 0, sin(angle), 0),
							Vector4f(0, 1, 0, 0),
							Vector4f(0, 0, 0, 1));
			break;
		}
		
	case 'z': {
			
			return Matrix4f(Vector4f(cos(angle), -sin(angle), 0, 0),
							Vector4f(sin(angle), cos(angle), 0, 0),
							Vector4f(0, 1, 0, 0),
							Vector4f(0, 0, 0, 1));
			break;
		}
	}
}
Matrix4f Matrix4f::scalingMatrix(Vector3f axisValues) {
	
	return Matrix4f(Vector4f(axisValues.x, 0, 0, 0),
					Vector4f(0, axisValues.y, 0, 0),
					Vector4f(0, 0, axisValues.z, 0),
					Vector4f(0, 0, 0, 1));
}
Matrix4f Matrix4f::translationMatrix(Vector3f axisValues) {
	
	return Matrix4f(Vector4f(1, 0, 0, axisValues.x),
					Vector4f(0, 1, 0, axisValues.y),
					Vector4f(0, 0, 1, axisValues.z),
					Vector4f(0, 0, 0, 1));
}
	
}//namespace maths