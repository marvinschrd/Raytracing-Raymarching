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

#include "maths/vector2.h"
#include "maths/vector3.h"

namespace maths {
	
//Class for column-based matrix 3x3
class Matrix3f {
	
public:
	
    Matrix3f() = default;

    Matrix3f(const Vector3f& v1, const Vector3f& v2, const Vector3f& v3);

    Matrix3f(const std::array<Vector3f, 3>& matrix) : matrix_(matrix) {}

    //This operator will return the column Vector2f at this position in the matrix.
    Vector3f& operator[](size_t index);

    //This operator will return the column Vector2f at this position in the matrix.
    const Vector3f& operator[](size_t index) const;
    
    Matrix3f operator+(const Matrix3f& rhs) const;

    Matrix3f& operator+=(const Matrix3f& rhs);

    Matrix3f operator-(const Matrix3f& rhs) const;

    Matrix3f& operator-=(const Matrix3f& rhs);

    Matrix3f operator*(const Matrix3f& rhs) const;

    Matrix3f& operator*=(const Matrix3f& rhs);

    Vector3f operator*(Vector3f rhs) const;

    Matrix3f& operator*=(float scalar);

	//This function returns the cofactor of the 3x3 matrix which can be used to find the determinant and adjoint matrix.
    float cofactor(int row, int column) const;

    //This function returns the determinant(float) of the 3x3 matrix.
    float determinant() const;

    //This function returns the inverse matrix of the 3x3 matrix.
    Matrix3f Inverse() const;

    //This function transposes the 3x3 matrix.
    Matrix3f Transpose() const;

	//This function returns the adjoint matrix which can be used to find the inverse of a matrix.
    Matrix3f adjoint() const;

    //This function returns true if the matrix's determinant is 1 and false otherwise.
    bool IsOrthogonal() const;

    //This function returns the identity matrix 3x3.
    static Matrix3f identity();

    //This function returns the rotation matrix 3x3 of the desired angle.
    static Matrix3f rotationMatrix(radian_t angle);

    //This function returns the scaling matrix 3x3 of the desired scaling values for x and y axis.
    static Matrix3f scalingMatrix(Vector2f axisValues);

    //This function returns the translation matrix 3x3 of the desired translation values for x and y axis.
    static Matrix3f translationMatrix(Vector2f axisValues);

private:

    std::array<Vector3f, 3> matrix_ {};
};
	
}//namespace maths