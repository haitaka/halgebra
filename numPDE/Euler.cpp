#include "Euler.h"

std::map< double, double > Euler(
		halg::Function const * func,
		std::string const & dFuncName,
		std::string const & dVarName,
		halg::Interval const & interval,
		double initArg, double initVal,
		halg::uint stepsCount
	)
{
	std::map< double, double > interpol;
	interpol[initArg] = initVal;

	double step = interval.Length() / stepsCount;
	for( halg::uint i = 0; i < stepsCount; ++i )
	{
		double prevArg = interpol.rbegin()->first;
		double prevVal = interpol.rbegin()->second;
		interpol[prevVal + step] =
				prevVal +
				step * func->Value(
							{ { dFuncName, prevVal },
							  { dVarName, prevArg } }
					   );
	}
	return interpol;
}
