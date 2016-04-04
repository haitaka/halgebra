#pragma once

#include "mathdefs.h"
#include "function.h"
#include <vector>
#include <map>

namespace halg
{
namespace Bound
{
	std::vector<Interval>
	bruteforce(Function * func, char var,
               std::map<char, double> var_vals,
			   Interval range, double step);
    std::vector<std::pair<Interval, Interval>>
    table2d(Function * func1, Function * func2,
            char var1, char var2,
            Interval range1, Interval range2,
            double step);
}
}
