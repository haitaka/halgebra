#include "Utils.h"

bool halg::IsInt( double val, double eps )
{
	return ( floor( val + 0.5 ) - eps <= val &&
			 val <= floor( val + 0.5 ) + eps );
}
