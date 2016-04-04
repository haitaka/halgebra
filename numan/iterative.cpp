#include "iterative.h"

Vector Iter::FixedP(Lin_System & sys, Vector x, double egn_min, double egn_max, double eps)
{
	//double tau = 1;
	double tau = 2 / (egn_min + egn_max);
	int icount = 0;
	Vector x_new(x.dimmension());
	while (true)
	{
		//x.print(stdout, 0, 3);
		x_new = (Vector)(x - (sys.A * x - sys.b)*tau);
		if (((Vector)(x_new - x)).inf_norm() < eps) 
		{
			printf("FP Iter count: %d\n", icount);
			return x_new;
		}
		x = x_new;
		icount++;
	}

	return x_new;
}

Vector Iter::Grad(Lin_System & sys, Vector x, double eps)
{
	Vector x_new(x.dimmension());
	int icount = 0;
	while (true)
	{
		//x.print(stdout, 0, 3);
		
		Matrix r = (sys.A * x - sys.b);
		Matrix atr = sys.A.transpose() * r;
		Matrix aatr = sys.A * atr;
		double lambd = scal(r, aatr)/scal(aatr,aatr);

		x_new = (Vector)(x - (atr * lambd));

		if (((Vector)(x_new - x)).inf_norm() < eps) 
		{
			printf("Grad Iter count: %d\n", icount);
			return x_new;
		}
		x = x_new;
		icount++;
	}

	return x_new;
}

Vector Iter::MinRes(Lin_System & sys, Vector x, double eps)
{
	Vector x_new(x.dimmension());
	int icount = 0;
	while (true)
	{
		//x.print(stdout, 0, 3);
		
		Matrix r = (sys.A * x - sys.b);
		Matrix ar = sys.A * r;
		double tau = scal(ar, r)/scal(ar,ar);

		x_new = (Vector)(x - (r * tau));

		if (((Vector)(x_new - x)).inf_norm() < eps) 
		{
			printf("MinRes Iter count: %d\n", icount);
			return x_new;
		}
		x = x_new;
		icount++;
	}

	return x_new;
}

Vector Iter::Relax(Lin_System & sys, Vector x, double w, double eps)
{
	int icount = 0;
	Vector x_new(x.dimmension());
	while (true)
	{
		//x.print(stdout, 0, 3);
		for (int i = 0; i < x.dimmension(); i++)
		{
			x_new[i] = sys.b[i];
			for (int j = 0; j < i; j++)
				x_new[i] -= sys.A[i][j] * x_new[j];
			for (int j = i + 1; j < x.dimmension(); j++)
				x_new[i] -= sys.A[i][j] * x[j];

			x_new[i] *= w / sys.A[i][i];
			x_new[i] += (1-w)*x[i];
		}

		if (((Vector)(x_new - x)).inf_norm() < eps)
		{
			printf("Relax Iter count: %d\n", icount);
			return x_new;
		}
		x = x_new;
		icount++;
	}

	return x_new;
}

Vector Iter::Jacobi(Lin_System & sys, Vector x, double eps)
{
	Vector x_new(x.dimmension());
	int icount = 0;
	while (true)
	{
		//x.print(stdout, 0, 3);
		for (int i = 0; i < x.dimmension(); i++)
		{
			x_new[i] = sys.b[i];
			for (int j = 0; j < x.dimmension(); j++)
				if (i != j) x_new[i] -= sys.A[i][j] * x[j];

			x_new[i] /= sys.A[i][i];
		}

		if (((Vector)(x_new - x)).inf_norm() < eps) 
		{
			printf("Jacobi Iter count: %d\n", icount);
			return x_new;
		}
		x = x_new;
		icount++;
	}

	return x_new;
}


Vector Iter::Power(Matrix & A, Vector & v, double eps)
{
	Vector v_new(v.dimmension());
	int icount = 0;
	while (true)
	{
		//v.print(stdout, 0, 3);
		v_new = (Vector)(A * v);
		v_new = (Vector)(v_new / v_new.inf_norm());
		if (((Vector)(v_new - v)).inf_norm() < eps) 
		{
			printf("Power Iter count: %d\n", icount);
			return v_new;
		}
		v = v_new;
		icount++;
	}

	return v_new;
}

// returning egn vectors mat & diag A
Matrix Iter::Egn_Jacobi(Matrix & A, double eps)
{
	Vector col_sum(A.col_order());
	Matrix I(A.row_order(), A.col_order());
	for (int i = 0; i < A.row_order(); ++i)
		for (int j = 0; j < A.col_order(); ++j)
			I[i][j] = (i == j);
	while (true)
	{
		//A.print(stdout, 0, 5);
		int row = 0;
		int col = 1;
		for (int i = 0; i < A.row_order(); ++i)
			for (int j = 0; j < A.col_order(); ++j)
				if (i != j && fabs(A[i][j]) > fabs(A[row][col]))
				{
					row = i;
					col = j;
				}

		double dbg = A[row][col];
		if (fabs(A[row][col]) < eps) return I;

		double angle;
		if (A[col][col] == A[row][row]) angle = atan(1.);
		else angle = atan(2 * A[row][col] / (A[row][row] - A[col][col])) / 2;

		Givens::rotate(A, row, col, angle);
		Givens::rotate(I, row, col, angle);
		Givens::rotateT(A, row, col, angle);
	}
}