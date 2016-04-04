#include "root_find.h"
using namespace halg;

Iter_report halg::bisection(Function * func, char var,
							Interval root_loc, double eps)
{
    Iter_report report;
    report.func = func;
	report.var = var;
	report.init = root_loc.left_val +
				  (root_loc.length() / 2);
    report.eps = eps;

    report.steps_count = 0;

	while (root_loc.length() > eps)
	{
        ++report.steps_count;

		double mid = root_loc.left_val +
					 (root_loc.length() / 2);
		if ((func->value(var, root_loc.left_val) *
             func->value(var, mid)) <= 0)
		{
			root_loc.right_val = mid;
		}
		else if ((func->value(var, mid) *
                  func->value(var, root_loc.right_val)) <= 0)
		{
			root_loc.left_val = mid;
		}
		else
		{
			throw except::No_roots();
		}
	}

    report.root = root_loc.left_val;
    return report;
}

Iter_report halg::nuton(Function * func, char var,
						double initial, double eps)
{
    Iter_report report;
	report.func = func;
	report.var = var;
	report.init = initial;
    report.eps = eps;

    report.steps_count = 0;

    Function * deriv = func->derivative(var);

	double approx = initial;

    while(true)
    {
        ++report.steps_count;

        double next_approx =
                approx -
				(func->value(var, approx) /
                 deriv->value(var, approx));

        if (fabs(next_approx - approx) < eps ||
            func->value(var, next_approx) == 0)
        {
            report.root = next_approx;
            return report;
        }
        approx = next_approx;
    }
}

Iter_report halg::iter(Function * func, char var,
					   double initial, double eps,
					   Function * iter_repres)
{
	Iter_report report;
	report.func = func;
	report.var = var;
	report.init = initial;
	report.eps = eps;

	report.steps_count = 0;

	double approx = initial;

	while(true)
	{
		++report.steps_count;

		double next_approx =
				iter_repres->value(var, approx);
        if (fabs(next_approx - approx) < eps ||
            func->value(var, next_approx) == 0)
		{
			report.root = next_approx;
			return report;
		}
        if (report.steps_count > 1024)
        {
            //throw except::Iter_divergention();
            std::cout << "divergention" << std::endl;
            report.root = sqrt(-1);
            return report;
        }
		approx = next_approx;
	}
}

Iter_report halg::relax(Function * func, char var,
                 double initial, double eps,
                 double tau)
{
    halg::Function * iter_repres =
            new halg::Sum(
                new halg::Var(var),
                new halg::Comp(
                    new halg::Const(tau),
                    func->copy()
                    )
                );
    return halg::iter(func, var, initial, eps, iter_repres);
}
