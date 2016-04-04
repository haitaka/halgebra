#include "tridiag.h"

Tridiag::Tridiag(int order)
{
	this->_order = order;
	this->init();
}

Tridiag::Tridiag(const Tridiag & src)
{
	this->_order = src._order;
	this->init();

	for (int i = 0; i < this->_order - 1; i++)
		this->_super[i] = src._super[i];

	for (int i = 0; i < this->_order; i++)
		this->_main[i] = src._main[i];

	for (int i = 0; i < this->_order - 1; i++)
		this->_sub[i] = src._sub[i];
}

Tridiag::~Tridiag()
{
	free(this->_super);
	free(this->_main);
	free(this->_sub);
}

void Tridiag::init()
{
	this->_super = (double *)calloc(this->_order - 1, sizeof(double));
	this->_main  = (double *)calloc(this->_order,     sizeof(double));
	this->_sub   = (double *)calloc(this->_order - 1, sizeof(double));
}

double Tridiag::get(int i, int j) const
{
	if (abs(i-j) > 1) return 0;
	
	if (i < j) return this->_super[i];
	if (i > j) return this->_sub[j];
	return this->_main[i];
}

int Tridiag::order() const
{
	return this->_order;
}

void Tridiag::print(FILE * stream, int width, int precision)
{
	for (int i = 0; i < this->order(); i++)
    {
        fprintf(stream, "[ ");
        for (int j = 0; j < this->order(); j++)
        {
            fprintf(stream, "% *.*lf ", width, precision, this->get(i, j));
        }
        fprintf(stream, " ]\n");
    }
    fprintf(stream, "\n");
}

void Tridiag::scan(FILE * stream)
{
    for (int i = 0; i < this->_order - 1; i++)
		fscanf(stream, "%lf", &(this->_super[i]));

	for (int i = 0; i < this->_order; i++)
		fscanf(stream, "%lf", &(this->_main[i]));

	for (int i = 0; i < this->_order - 1; i++)
		fscanf(stream, "%lf", &(this->_sub[i]));
}

Tridiag::operator Matrix()
{
	Matrix Result(this->order());

	for (int i = 0; i < this->order(); i++)
		for (int j = 0; j < this->order(); j++)
			Result[i][j] = this->get(i, j);

	return Result;
}


Vector Tridiag::shuttle(Vector & b)
{
	int size = this->order();
	Vector x(size);

	for (int i = 1; i < size; i++) 
	{
		this->_main[i] -= this->_sub[i-1] * this->_super[i-1] / this->_main[i-1];
		b[i]           -= this->_sub[i-1] * b[i-1]            / this->_main[i-1];
	}

	x[size-1] = b[size-1] / this->_main[size-1];
	for (int i = size - 2; i >= 0; i--) 
		x[i] = (b[i] - this->_super[i] * x[i+1]) / this->_main[i];

	return x;
}