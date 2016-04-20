#include "Adams.h"
#include <iostream>

std::map< double, std::pair< double, double > > halg::Adams(
        halg::Function const * func1,
        halg::Function const * func2,
        std::string const & dFuncName1,
        std::string const & dFuncName2,
        std::string const & dVarName,
        halg::Interval const & interval,
        double initArg1, double initVal1,
        double initArg2, double initVal2,
        halg::uint frequency
    )
{
    std::map< double, std::pair< double, double > > interpol;
    interpol[initArg1] = std::make_pair(initVal1, initVal2);

    double step = interval.Length() / frequency;
    for( halg::uint i = 0; i < frequency; ++i )
    {
        double prevArg = interpol.rbegin()->first;
        double prevVal1 = interpol.rbegin()->second.first;
        double prevVal2 = interpol.rbegin()->second.second;

        double f1 = func1->Value( {{ dFuncName1, prevVal1 },
                                   { dFuncName2, prevVal2 },
                                   { dVarName, prevArg }} );
        double f2 = func2->Value( {{ dFuncName1, prevVal1 },
                                   { dFuncName2, prevVal2 },
                                   { dVarName, prevArg }} );
        double newArg = prevArg + step;
        double newVal1 = prevVal1 + step * f1;
        double newVal2 = prevVal2 + step * f2;

        interpol[newArg] = std::make_pair(newVal1, newVal2);
    }
    return interpol;
}
