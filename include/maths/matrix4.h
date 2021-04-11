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

#include "maths/vector3.h"
#include "maths/vector4.h"

namespace maths
{
//Class for column-based matrix 4x4
class Matrix4f
{
public:

    Matrix4f() = default;

    Matrix4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& v4);

    Matrix4f(const std::array<Vector4f, 4>& matrix) : matrix_(matrix) {}

    //This operator will return the column Vector2f at this position in the matrix.
    Vector4f& operator[](std::size_t index);

    //This operator will return the column Vector2f at this position in the matrix.
    const Vector4f& operator[](std::size_t index) const;
    
    Matrix4f operator+(const Matrix4f& rhs) const;

    Matrix4f& operator+=(const Matrix4f& rhs);

    Matrix4f operator-(const Matrix4f& rhs) const;

    Matrix4f& operator-=(const Matrix4f& rhs);

    Matrix4f operator*(const Matrix4f& rhs) const;

    Matrix4f& operator*=(const Matrix4f& rhs);

    Vector4f operator*(Vector4f rhs) const;

    Matrix4f& operator*=(float scalar);

    //This function returns the cofactor of the 3x3 matrix who can be used to find the determinant and adjoint matrix
    float cofactor(int row, int column) const;

    //This function returns the determinant(float) of the 4x4 matrix
    float determinant() const;

    //This function returns the inverse matrix of the 4x4 matrix
    Matrix4f Inverse() const;

    //This function transposes the 4x4 matrix
    Matrix4f Transpose() const;

    //This function returns the adjoint matrix which can be used to finc the inverse of a matrix
    Matrix4f adjoint() const;

    //This function returns true if the matrix's determinant is 1 and false otherwise
    bool IsOrthogonal() const;

    //This function returns the identity matrix 4x4
    static Matrix4f identity();

    //This function returns the rotation matrix 4x4 of the desired angle and given axis.
    static Matrix4f rotationMatrix(radian_t angle, char axis);

    //This function returns the scaling matrix 4x4 of the desired scaling values for x, y and z axis.
    static Matrix4f scalingMatrix(Vector3f axisValues);

    //This function returns the translation matrix 3x3 of the desired translation values for x, y and z axis.
    static Matrix4f translationMatrix(Vector3f axisValues);

private:

    std::array<Vector4f, 4> matrix_ {};
};
	
}//namespace maths


