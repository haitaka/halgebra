#pragma once

#include <map>

#include "NumPDE.h"

namespace halg
{
	std::map< double, double > Euler(
			halg::Function const * func,
			std::string const & dFuncName,
			std::string const & dVarName,
			halg::Interval const & interval,
			double initArg, double initVal,
			halg::uint stepsCount
		);
}
