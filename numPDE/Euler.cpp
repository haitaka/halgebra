#include "Euler.h"

std::map< double, double > halg::Euler(
		halg::Function const * func,
		std::string const & dFuncName,
		std::string const & dVarName,
		halg::Interval const & interval,
		double initArg, double initVal,
		halg::uint frequency
	)
{
	std::map< double, double > interpol;
	interpol[initArg] = initVal;

	double step = interval.Length() / frequency;
	for( halg::uint i = 0; i < frequency; ++i )
	{
		double prevArg = interpol.rbegin()->first;
		double prevVal = interpol.rbegin()->second;

		double f = func->Value( {{ dFuncName, prevVal },
								 { dVarName, prevArg }} );
		double newArg = prevArg + step;
		double newVal = prevVal + step * f;

		interpol[newArg] = newVal;
	}
	return interpol;
}
