#include "givens.h"

Givens::QR_Decomp::QR_Decomp(int rows, int cols) : Q(rows, cols), R(rows, cols) {}

void Givens::elimination(Lin_System & sys)
{
    for (int j = 0; j < sys.A.col_order() - 1; j++) {
		for (int i = j + 1; i < sys.A.row_order(); i++) {

			double angle = atan(sys.A[i][j] / sys.A[j][j]);

			rotateT(sys, i, j, angle);
		}
	}
}

Givens::QR_Decomp Givens::QR(Matrix & A)
{
	Givens::QR_Decomp decomp(A.row_order(), A.col_order());
	decomp.R = A;
	for (int i = 0; i < decomp.Q.row_order(); i++)
		for (int j = 0; j < decomp.Q.col_order(); j++)
			decomp.Q[i][j] = (i == j);

	for (int j = 0; j < decomp.R.col_order() - 1; j++) {
		for (int i = j + 1; i < decomp.R.row_order(); i++) {

			double angle = atan(decomp.R[i][j] / decomp.R[j][j]);

			rotateT(decomp.R, i, j, angle);
			rotateT(decomp.Q, i, j, angle);
		}
	}

	decomp.Q = Gauss::Inverse_lc(decomp.Q);
	return decomp;
}


void Givens::rotateT(Lin_System & sys, int k, int l, double angle)
{
	Givens::rotateT(sys.A, k, l, angle);

	double tmp_i = sys.b[k] * cos(angle) - sys.b[l] * sin(angle);
	double tmp_j = sys.b[k] * sin(angle) + sys.b[l] * cos(angle);
	sys.b[k] = tmp_i;
	sys.b[l] = tmp_j;
}

void Givens::rotateT(Matrix & A, int k, int l, double angle)
{
	for (int j = 0; j < A.col_order(); j++) {
		double tmp_kj = A[k][j] * cos(angle) - A[l][j] * sin(angle);
		double tmp_lj = A[k][j] * sin(angle) + A[l][j] * cos(angle);

		A[k][j] = tmp_kj;
		A[l][j] = tmp_lj;
	}
}

void Givens::rotate(Matrix & A, int k, int l, double angle)
{
	for (int i = 0; i < A.row_order(); i++) {
		double tmp_ik = A[i][k] *    cos(angle) + A[i][l] * sin(angle);
		double tmp_il = A[i][k] * (-sin(angle)) + A[i][l] * cos(angle);

		A[i][k] = tmp_ik;
		A[i][l] = tmp_il;
	}
}
