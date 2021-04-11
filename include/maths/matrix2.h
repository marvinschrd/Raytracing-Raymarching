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

namespace maths {
	
//Class for column-based matrix 2x2
class Matrix2f {
	
public:
    
    Matrix2f() = default;

    Matrix2f(const Vector2f& v1, const Vector2f& v2);

	Matrix2f(const std::array<Vector2f, 2>& matrix) : matrix_(matrix) {}

	//This operator will return the column Vector2f at this position in the matrix.
    Vector2f& operator[](std::size_t index);

    //This operator will return the column Vector2f at this position in the matrix.
    const Vector2f& operator[](std::size_t index) const;

    Matrix2f operator+(const Matrix2f& rhs) const;

    Matrix2f& operator+=(const Matrix2f& rhs);

    Matrix2f operator-(const Matrix2f& rhs) const;

    Matrix2f& operator-=(const Matrix2f& rhs);

    Matrix2f operator*(const Matrix2f& rhs) const;

    Matrix2f& operator*=(const Matrix2f& rhs);

    Matrix2f& operator*=(float scalar);

    Vector2f operator*(Vector2f rhs) const;

	//This function returns the determinant(float) of the 2x2 matrix
    float determinant() const;

	//This function returns the inverse matrix of the 2x2 matrix
    Matrix2f Inverse() const;

	//This function transposes the 2x2 matrix 
    Matrix2f Transpose() const;

	//This function returns true if the matrix's determinant is 1 and false otherwise
    bool IsOrthogonal() const;

	//This function returns the identity matrix 2x2
    static Matrix2f identity();

private:

    std::array<Vector2f, 2> matrix_ {};
};
}//namespace maths