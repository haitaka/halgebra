#pragma once

#include <math.h>
#include "linsys.h"
#include "tridiag.h"
#include "gauss.h"

namespace Givens
{
	struct QR_Decomp {
		Matrix Q;
		Matrix R;
		QR_Decomp(int rows, int cols);
	};

	void    elimination(Lin_System & sys);
	QR_Decomp QR(Matrix & A);

	void rotate(Matrix & A, int i, int j, double angle);
	void rotateT(Matrix & A, int i, int j, double angle);
	void rotateT(Lin_System & sys, int i, int j, double angle);
};