#pragma once

#include "mathdefs.h"
#include "function.h"
#include <cmath>

namespace halg
{
    double golden_sect(Function * func, char var,
                       double section,
                       Interval interval,
                       double eps);
}
