#pragma once

#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include "linsys.h"

class Tridiag
{
public:
	double * _super;
	double * _main;
	double * _sub; 
	int      _order;

private:
	void init();
public:
	Tridiag(int order);
	Tridiag(const Tridiag & src);
	~Tridiag();
	
	int order() const;
	double get(int i, int j) const;

	void print(FILE * stream, int width, int precision);
	void scan(FILE * stream);

	operator Matrix();

	Vector shuttle(Vector & b);
};