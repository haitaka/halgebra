#pragma once

#include "linsys.h"

namespace Gauss
{
	struct LU_Decomp {
		Matrix L;
		Matrix U;
		LU_Decomp(int rows, int cols);
	};

	void      elimination(Lin_System & sys);
	Matrix   Inverse(Matrix & orig);
	LU_Decomp LU(Matrix & A);

	void      elimination_lc(Lin_System & sys);
	Matrix    Inverse_lc(Matrix & orig);
	LU_Decomp LU_lc(Matrix & A);
};