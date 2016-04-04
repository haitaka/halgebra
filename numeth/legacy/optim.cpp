#include "optim.h"

bool gs_right_is_longer(halg::Interval interval,
                        double section)
{
    return (interval.right_val - section) >
           (section - interval.left_val);
}

double halg::golden_sect(halg::Function * func, char var,
                         double section,
                         halg::Interval interval,
                         double eps)
{
    double new_section;

    if (gs_right_is_longer(interval, section))
    {
        new_section = section +
                      ((2 - halg::GOLD_RATIO) *
                       (interval.right_val - section));
    }
    else
    {
        new_section = section -
                      ((2 - halg::GOLD_RATIO) *
                       (section - interval.left_val));
    }
    if (interval.length() <=
        eps * (fabs(section) + fabs(new_section)))
    {
        return interval.mid();
    }
    if (func->value(var, new_section) <
        func->value(var, section))
    {
        if (gs_right_is_longer(interval, section))
        {
            return halg::golden_sect(
                        func, var,
                        new_section,
                        halg::Interval(
                            section,
                            interval.right_val
                            ),
                        eps);
        }
        return halg::golden_sect(
                    func, var,
                    new_section, interval,
                    eps);
    }
    else
    {
        if (gs_right_is_longer(interval, section))
        {
            return halg::golden_sect(
                        func, var,
                        section,
                        halg::Interval(
                            interval.left_val,
                            new_section
                            ),
                        eps);
        }
        return halg::golden_sect(
                    func, var,
                    section, halg::Interval(
                        new_section,
                        interval.right_val
                        ),
                    eps);
    }
}
