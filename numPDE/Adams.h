#pragma once

/* y_{i+1} = y_i + h*f(x_i,y_i)
 * Задача Коши имеет ед. решение,
 * если f(x,y) непрерывна по x и Липшецева по второму.
 * Локальная погрешность O(h^2), глобальная O(h)
 */

#include <map>

#include "NumPDE.h"
#include "../VectorFunc.h"

namespace halg
{
    /*std::map< halg::Vector< double >, halg::Vector< double >>
        Adams(
            halg::VectorFunc const func,
            std::string const & dFuncName, //vector?
            std::string const & dVarName,
            halg::Interval const & interval,
            halg::Vector< double > initArg,
            halg::Vector< double > initVal,
            halg::uint frequency
        );*/
    std::map< double, std::pair< double, double > > Adams(
            halg::Function const * func1,
            halg::Function const * func2,
            std::string const & dFuncName1,
            std::string const & dFuncName2,
            std::string const & dVarName,
            halg::Interval const & interval,
            double initArg1, double initVal1,
            double initArg2, double initVal2,
            halg::uint frequency
        );

}
