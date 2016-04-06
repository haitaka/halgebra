#include "RungeKutta.h"

std::map< double, double > halg::RungeKutta(
		halg::Function const * func,
		std::string const & dFuncName,
		std::string const & dVarName,
		halg::Interval const & interval,
		double initArg, double initVal,
		halg::uint frequency,
		double aParam
	)
{
	std::map< double, double > interpol;
	interpol[initArg] = initVal;

	double c1Param = 1 - 1 / ( 2 * aParam );
	double c2Param = 1 / ( 2 * aParam );
	double bParam = aParam;

	double step = interval.Length() / frequency;
	for( halg::uint i = 0; i < frequency; ++i )
	{
		double prevArg = interpol.rbegin()->first;
		double prevVal = interpol.rbegin()->second;

		double f1 = func->Value(
			{{ dFuncName, prevVal },
			 { dVarName, prevArg }}
		);
		double k1 = c1Param * f1;
		double f2 = func->Value(
			{{ dFuncName, prevVal + bParam * k1 * step },
			 { dVarName, prevArg + aParam * step }}
		);
		double k2 = c2Param * f2;

		double newArg = prevArg + step;
		double newVal = prevVal + step * ( k1 + k2 );

		interpol[newArg] = newVal;
	}
	return interpol;
}
