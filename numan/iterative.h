#pragma once

#include "linsys.h"
#include "givens.h"

namespace Iter
{
	Vector FixedP(Lin_System & sys, Vector x, double egn_min, double egn_max, double eps);
	Vector Grad(Lin_System & sys, Vector x, double eps);
	Vector MinRes(Lin_System & sys, Vector x, double eps);
	Vector Relax(Lin_System & sys, Vector x, double w, double eps);
	Vector Jacobi(Lin_System & sys, Vector x, double eps);

	Vector Power(Matrix & A, Vector & b, double eps);


	Matrix Egn_Jacobi(Matrix & A, double eps);
}