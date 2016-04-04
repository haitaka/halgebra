#include "linsys.h"

Lin_System::Lin_System(int cols, int rows) : A(cols, rows), b(rows) {}

void Lin_System::print(FILE * stream, int width, int precision)
{
    for (int i = 0; i < this->A.row_order(); i++)
    {
        fprintf(stream, "[ ");
        for (int j = 0; j < this->A.col_order(); j++)
        {
            fprintf(stream, "% *.*lf ", width, precision, this->A[i][j]);
        }
        fprintf(stream, "| ");
        fprintf(stream, "% *.*lf",  width, precision, this->b[i]);
        fprintf(stream, " ]\n");
    }
    fprintf(stream, "\n");
}

Vector Lin_System::reverse_solve()
{
	int size = b.dimmension();
	Vector x(size);

    for (int i = size - 1; i >= 0; i--)
    {
        double tmp = this->b[i];
        for (int j = i + 1; j < size; j++)
        {
            tmp -= this->A[i][j] * x[j];
        }
        x[i] = tmp / this->A[i][i];
    }

    return x;
}