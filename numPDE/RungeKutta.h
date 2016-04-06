#pragma once

/* y_{i+1} = y_i + h*f(x_i,y_i)
 * Задача Коши имеет ед. решение,
 * если f(x,y) непрерывна по x и Липшецева по второму.
 * Локальная погрешность O(h^2), глобальная O(h)
 */

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
