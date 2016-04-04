#include "gauss.h"

Gauss::LU_Decomp::LU_Decomp(int rows, int cols) : L(rows, cols), U(rows, cols) {}

void Gauss::elimination(Lin_System & sys)
{
    for (int k = 0; k < sys.A.row_order(); k++)
    {
        double div = 1 / sys.A[k][k];
        sys.A.row(k) *= div;
        sys.b[k] *= div;

        for (int i = k + 1; i < sys.A.row_order(); i++)
        {
			double mul = sys.A[i][k];
			sys.A.row(i) -= sys.A.row(k) * mul;
            sys.b[i]     -= sys.b[k]     * mul;
        }
    }
}

Matrix Gauss::Inverse(Matrix & orig)
{
    Matrix     Inverse(orig.row_order(), orig.col_order());
    Lin_System tmp_sys(orig.row_order(), orig.col_order());

    for (int k = 0; k < orig.col_order(); k++)
    {
        for (int i = 0; i < orig.row_order(); i++)
            tmp_sys.b[i] = (i==k);

        tmp_sys.A = orig;

		Gauss::elimination(tmp_sys);
        Vector x = tmp_sys.reverse_solve();

        for (int i = 0; i < orig.row_order(); i++)
        {
			Inverse[i][k] = x[i];
        }
    }

    return Inverse;
}

Gauss::LU_Decomp Gauss::LU(Matrix & A)
{
	Gauss::LU_Decomp decomp(A.row_order(), A.col_order());
	decomp.U = A;

    for (int k = 0; k < decomp.U.row_order(); k++)
    {
        for (int i = k; i < decomp.U.row_order(); i++)
        {
			decomp.L[i][k] = decomp.U[i][k];
        }

        decomp.U.row(k) *= (1 / decomp.U[k][k]);
        for (int i = k + 1; i < decomp.U.row_order(); i++)
        {
			decomp.U.row(i) -= decomp.U.row(k) * decomp.U[i][k];
        }
    }

    return decomp;
}

void Gauss::elimination_lc(Lin_System & sys)
{

    for (int k = 0; k < sys.A.row_order(); k++)
    {
		int lead_row = sys.A.col(k).get_max(k);
		sys.A.row_swap(k, lead_row);
		sys.b.row_swap(k, lead_row);
		
        double div = 1 / sys.A[k][k];
        sys.A.row(k) *= div;
        sys.b[k] *= div;

        for (int i = k + 1; i < sys.A.row_order(); i++)
        {
			double mul = sys.A[i][k];
			sys.A.row(i) -= sys.A.row(k) * mul;
            sys.b[i]     -= sys.b[k]     * mul;
        }
    }
}

Matrix Gauss::Inverse_lc(Matrix & orig)
{
    Matrix     Inverse(orig.row_order(), orig.col_order());
    Lin_System tmp_sys(orig.row_order(), orig.col_order());

    for (int k = 0; k < orig.col_order(); k++)
    {
        for (int i = 0; i < orig.row_order(); i++)
            tmp_sys.b[i] = (i==k);

        tmp_sys.A = orig;

        Gauss::elimination_lc(tmp_sys);
        Vector x = tmp_sys.reverse_solve();

        for (int i = 0; i < orig.row_order(); i++)
        {
			Inverse[i][k] = x[i];
        }
    }

    return Inverse;
}

Gauss::LU_Decomp Gauss::LU_lc(Matrix & A)
{
	Gauss::LU_Decomp decomp(A.row_order(), A.col_order());
	decomp.U = A;

    for (int k = 0; k < decomp.U.row_order(); k++)
    {
        
		int lead_row = decomp.U.col(k).get_max(k);
		decomp.U.row_swap(k, lead_row);
		

        for (int i = k; i < decomp.U.row_order(); i++)
        {
			decomp.L[i][k] = decomp.U[i][k];
        }

        decomp.U.row(k) *= (1 / decomp.U[k][k]);
        for (int i = k + 1; i < decomp.U.row_order(); i++)
        {
			decomp.U.row(i) -= decomp.U.row(k) * decomp.U[i][k];
        }
    }

    return decomp;
}