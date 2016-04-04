#pragma once

#include "function.h"
#include "mathdefs.h"
#include "exceptions.h"
#include "report.h"
#include "root_find.h"

namespace halg {
    struct Iter_report_2d
    {
        Function * func1;
        Function * func2;
        double root1;
        double root2;
        int steps_count;
    };

    Iter_report_2d iter_2d(
                    Function * func1, Function * func2,
                    char var1, char var2,
                    double init1, double init2,
                    double eps);

    Iter_report_2d nuton_2d(Function * func1, Function * func2,
                         char var1, char var2,
                         double init1, double init2,
                         double eps);
    Iter_report_2d nuton_approx_2d(
                    Function * func1, Function * func2,
                    char var1, char var2,
                    double init1, double init2,
                    double eps);
}
