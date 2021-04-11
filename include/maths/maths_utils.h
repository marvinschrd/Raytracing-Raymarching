#pragma once

#include <cmath>

namespace maths {

//This function takes 2 floats and returns true if the 2 are equal and false otherwise.
//You can also add an epsilon to the argument list if you don't want the default.
inline bool Equal(float a, float b, float epsilon = 0.0000001f) {
	
	return std::abs(a - b) < epsilon;
}
}