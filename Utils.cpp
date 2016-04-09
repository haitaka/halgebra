#include "Utils.h"

bool halg::IsInt( double val, double eps )
{
	return ( floor( val + 0.5 ) - eps <= val &&
			 val <= floor( val + 0.5 ) + eps );
}

double halg::RandDouble( double min, double max )
{
    double f = (double)rand() / 9999;
    return min + f * ( max - min );
}
