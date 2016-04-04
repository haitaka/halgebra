#pragma once

#include "function.h"
#include "mathdefs.h"
#include "exceptions.h"
#include "report.h"

namespace halg {
    struct Iter_report
    {
        Function * func;
        char var;
		double init;
        double eps;
        double root;
        int steps_count;
        //double initial;
    };

    Iter_report bisection(Function * func, char var,
						  Interval root_loc, double eps);
    Iter_report nuton(Function * func, char var,
					  double initial, double eps);
	Iter_report iter(Function * func, char var,
					 double initial, double eps,
					 Function * iter_repres);
    Iter_report relax(Function * func, char var,
                     double initial, double eps,
                     double tau);
}
