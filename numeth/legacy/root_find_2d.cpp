#include "root_find_2d.h"

std::vector< halg::Function * >
iter_2d_parameter(halg::Function * func1, halg::Function * func2,
                  char var1, char var2,
                  std::map<char, double> var_vals)
{
    std::vector< halg::Function * > param;

    halg::Function * d1v1 = func1->derivative(var1);
    halg::Function * d1v2 = func1->derivative(var2);
    halg::Function * d2v1 = func2->derivative(var1);
    halg::Function * d2v2 = func2->derivative(var2);

    halg::Function * det = new halg::Diff(
             new halg::Comp(d1v1->copy(), d2v2->copy()),
             new halg::Comp(d1v2->copy(), d2v1->copy())
         );
    halg::Function * antidet = new halg::Div(
                                   new halg::Const(1),
                                   det
                               );
    param.push_back(new halg::Diff(
                        new halg::Comp(
                            new halg::Var(var1),
                            new halg::Const(d2v2->copy()->value(var_vals)),
                            antidet->copy()
                            ),
                        new halg::Comp(
                            new halg::Var(var2),
                            new halg::Const(d1v2->copy()->value(var_vals)),
                            antidet->copy()
                            )
                        ));
    param.push_back(new halg::Diff(
                        new halg::Comp(
                            new halg::Var(var2),
                            new halg::Const(d1v1->copy()->value(var_vals)),
                            antidet->copy()
                            ),
                        new halg::Comp(
                            new halg::Var(var1),
                            new halg::Const(d2v1->copy()->value(var_vals)),
                            antidet->copy()
                            )
                        ));
    /*delete d1v1;
    delete d2v1;
    delete d1v2;
    delete d2v2;
    delete antidet;*/

    return param;
}

std::vector< halg::Function * >
nuton_2d_parameter(halg::Function * func1, halg::Function * func2,
                   char var1, char var2)
{
    std::vector< halg::Function * > param;

    halg::Function * d1v1 = func1->derivative(var1);
    halg::Function * d1v2 = func1->derivative(var2);
    halg::Function * d2v1 = func2->derivative(var1);
    halg::Function * d2v2 = func2->derivative(var2);

    halg::Function * det = new halg::Diff(
             new halg::Comp(d1v1->copy(), d2v2->copy()),
             new halg::Comp(d1v2->copy(), d2v1->copy())
         );
    halg::Function * antidet = new halg::Div(
                                   new halg::Const(1),
                                   det
                               );
    param.push_back(new halg::Diff(
                        new halg::Comp(
                            new halg::Var(var1),
                            d2v2->copy(),
                            antidet->copy()
                            ),
                        new halg::Comp(
                            new halg::Var(var2),
                            d1v2->copy(),
                            antidet->copy()
                            )
                        ));
    param.push_back(new halg::Diff(
                        new halg::Comp(
                            new halg::Var(var2),
                            d1v1->copy(),
                            antidet->copy()
                            ),
                        new halg::Comp(
                            new halg::Var(var1),
                            d2v1->copy(),
                            antidet->copy()
                            )
                        ));
    /*delete d1v1;
    delete d2v1;
    delete d1v2;
    delete d2v2;
    delete antidet;*/

    return param;
}

std::vector< halg::Function * >
nuton_2d_param_approx(halg::Function * func1, halg::Function * func2,
                   char var1, char var2,
                   std::map<char, double> var_vals,
                   double h)
{
    std::vector< halg::Function * > param;

    std::map<char, double> var_vals2 = var_vals;
    var_vals2[var1] += h;
    halg::Function * d1v1 = new halg::Const(
                                (new halg::Div(
                                    new halg::Diff(
                                        new halg::Const(func1->value(var_vals2)),
                                        new halg::Const(func1->value(var_vals))
                                    ),
                                 new halg::Const(h)
                                 ))->value({})
                            );
    halg::Function * d2v1 = new halg::Const(
                                (new halg::Div(
                                    new halg::Diff(
                                        new halg::Const(func2->value(var_vals2)),
                                        new halg::Const(func2->value(var_vals))
                                    ),
                                 new halg::Const(h)
                                ))->value({})
                            );
    var_vals2 = var_vals;
    var_vals2[var2] += h;
    halg::Function * d1v2 = new halg::Const(
                                (new halg::Div(
                                    new halg::Diff(
                                        new halg::Const(func1->value(var_vals2)),
                                        new halg::Const(func1->value(var_vals))
                                    ),
                                 new halg::Const(h)
                                ))->value({})
                            );
    halg::Function * d2v2 = new halg::Const(
                                (new halg::Div(
                                    new halg::Diff(
                                        new halg::Const(func2->value(var_vals2)),
                                        new halg::Const(func2->value(var_vals))
                                    ),
                                 new halg::Const(h)
                                ))->value({})
                            );

    halg::Function * det = new halg::Diff(
             new halg::Comp(d1v1->copy(), d2v2->copy()),
             new halg::Comp(d1v2->copy(), d2v1->copy())
         );
    halg::Function * antidet = new halg::Div(
                                   new halg::Const(1),
                                   det
                               );
    param.push_back(new halg::Diff(
                        new halg::Comp(
                            new halg::Var(var1),
                            d2v2->copy(),
                            antidet->copy()
                            ),
                        new halg::Comp(
                            new halg::Var(var2),
                            d1v2->copy(),
                            antidet->copy()
                            )
                        ));
    param.push_back(new halg::Diff(
                        new halg::Comp(
                            new halg::Var(var2),
                            d1v1->copy(),
                            antidet->copy()
                            ),
                        new halg::Comp(
                            new halg::Var(var1),
                            d2v1->copy(),
                            antidet->copy()
                            )
                        ));
    /*delete d1v1;
    delete d2v1;
    delete d1v2;
    delete d2v2;
    delete antidet;*/

    return param;
}

halg::Iter_report_2d halg::iter_2d(
                halg::Function * func1, halg::Function * func2,
                char var1, char var2,
                double init1, double init2,
                double eps)
{
    Iter_report_2d report;
    report.func1 = func1;
    report.func2 = func2;
    report.steps_count = 0;

    std::vector< halg::Function * > param =
            iter_2d_parameter(func1, func2, var1, var2,
                              {{var1, init1},{var2, init2}});

    double x = init1;
    double y = init2;



    while(true)
    {
        ++report.steps_count;

        // этот код уже ничто не испортит
        double f1 = func1->value({{var1, x}, {var2, y}});
        double f2 = func2->value({{var1, x}, {var2, y}});
        double x_new =
                x - param[0]->value({{var1, f1}, {var2, f2}});
        double y_new =
                y - param[1]->value({{var1, f1}, {var2, f2}});

        if (sqrt(pow(x_new-x, 2) + pow(y_new - y, 2)) < eps ||
            (func1->value({{var1, x_new}, {var2, y_new}}) == 0 &&
            func2->value({{var1, x_new}, {var2, y_new}}) == 0))
        {
            report.root1 = x_new;
            report.root2 = y_new;
            return report;
        }
        x = x_new;
        y = y_new;
    }
}

halg::Iter_report_2d halg::nuton_2d(
                halg::Function * func1, halg::Function * func2,
                char var1, char var2,
                double init1, double init2,
                double eps)
{
    Iter_report_2d report;
    report.func1 = func1;
    report.func2 = func2;
    report.steps_count = 0;

    std::vector< halg::Function * > param =
            nuton_2d_parameter(func1, func2, var1, var2);

    double x = init1;
    double y = init2;

    while(true)
    {
        ++report.steps_count;

        // этот код уже ничто не испортит
        double f1 = func1->value({{var1, x}, {var2, y}});
        double f2 = func2->value({{var1, x}, {var2, y}});
        double x_new =
                x - param[0]->value({{var1, f1}, {var2, f2}});
        double y_new =
                y - param[1]->value({{var1, f1}, {var2, f2}});

        if (sqrt(pow(x_new-x, 2) + pow(y_new - y, 2)) < eps ||
            (func1->value({{var1, x_new}, {var2, y_new}}) == 0 &&
            func2->value({{var1, x_new}, {var2, y_new}}) == 0))
        {
            report.root1 = x_new;
            report.root2 = y_new;
            return report;
        }
        x = x_new;
        y = y_new;
    }
}

halg::Iter_report_2d halg::nuton_approx_2d(
                halg::Function * func1, halg::Function * func2,
                char var1, char var2,
                double init1, double init2,
                double eps)
{
    Iter_report_2d report;
    report.func1 = func1;
    report.func2 = func2;
    report.steps_count = 0;

    double x = init1;
    double y = init2;

    while(true)
    {
        ++report.steps_count;

        std::vector< halg::Function * > param =
                nuton_2d_param_approx(func1, func2, var1, var2,
                                      {{var1, x}, {var2, y}},1);
        // этот код уже ничто не испортит
        double f1 = func1->value({{var1, x}, {var2, y}});
        double f2 = func2->value({{var1, x}, {var2, y}});
        double x_new =
                x - param[0]->value({{var1, f1}, {var2, f2}});
        double y_new =
                y - param[1]->value({{var1, f1}, {var2, f2}});

        if (sqrt(pow(x_new-x, 2) + pow(y_new - y, 2)) < eps ||
            (func1->value({{var1, x_new}, {var2, y_new}}) == 0 &&
            func2->value({{var1, x_new}, {var2, y_new}}) == 0))
        {
            report.root1 = x_new;
            report.root2 = y_new;
            return report;
        }
        x = x_new;
        y = y_new;
    }
}
