#include "bounding.h"
using namespace halg;

std::vector<Interval>
Bound::bruteforce(Function * func, char var,
                  std::map<char, double> var_vals,
				  Interval range, double step)
{
	std::vector<Interval> root_locations;

	for (double x = range.left_val;
		 x <= range.right_val - step;
		 x += step)
	{
        var_vals[var] = x;
        std::map<char,double> var_vals2 = var_vals;
        var_vals2[var] = x + step;
        if ((func->value(var_vals) *
             func->value(var_vals2)) < 0)
		{
			root_locations.insert(
						root_locations.end(),
						Interval(x, x + step)
						);
		}
        if (func->value(var_vals) == 0)
        {
            root_locations.insert(
                        root_locations.end(),
                        Interval(x, x)
                        );
        }
	}
	return root_locations;
}

std::vector<std::pair<Interval, Interval>>
Bound::table2d(Function * func1, Function * func2,
               char var1, char var2,
               Interval range1, Interval range2,
               double step)
{
    std::vector<std::pair<Interval, Interval>> root_locs;

    std::vector<std::vector<std::pair<double, double>>> table;

    for (double x = range1.left_val;
         x <= range1.right_val - step;
         x += step)
    {
        std::vector<std::pair<double, double>> row;
        for (double y = range2.left_val;
             y <= range2.right_val - step;
             y += step)
        {
            std::map<char, double> var_vals;
            var_vals[var1] = x;
            var_vals[var2] = y;

            row.push_back(std::make_pair(
                              func1->value(var_vals),
                              func2->value(var_vals)
                              ));
        }
        table.push_back(row);
    }
    for(int i = 1, i_size = table.size();
        i < i_size;
        ++i)
    {
        for(int j = 1, j_size = table[i].size();
            j < j_size;
            ++j)
        {
            if (table[i][j].first * table[i-1][j-1].first < 0 &&
                table[i][j].second * table[i-1][j-1].second < 0)
            {
                root_locs.push_back(std::make_pair(
                                        Interval(range1.left_val + step*(i-1),
                                                 range1.left_val + step*(i)),
                                        Interval(range2.left_val + step*(j-1),
                                                 range2.left_val + step*(j))
                                        ));
            }
        }
    }
    return root_locs;
}
