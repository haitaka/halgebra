#pragma once

#include "matrix.h"
#include "vector.h"
#include "math.h"

class Lin_System
{
public:
	Matrix A;
	Vector b;
	Lin_System(int cols, int rows);
	Lin_System(int size) : A(size, size), b(size) {}

	void print(FILE * stream, int width, int precision);
	Vector reverse_solve();
};
