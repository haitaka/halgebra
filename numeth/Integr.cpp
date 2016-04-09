#include "Integr.h"

double halg::TrapezRule::operator () (
						halg::Function const * func,
						std::string const & varName,
						halg::Interval const & interval
					) const
{
	double f_a = func->Value( {{ varName,
								 interval.Left() }} );
	double f_b = func->Value( {{ varName,
								 interval.Right() }} );

	return interval.Length() * ( f_a + f_b ) / 2;
}

double halg::SimpsonRule::operator () (
						halg::Function const * func,
						std::string const & varName,
						halg::Interval const & interval
					) const
{
	double f_a = func->Value( {{ varName,
								 interval.Left() }} );
	double f_mid = func->Value( {{ varName,
								   interval.Mid() }} );
	double f_b = func->Value( {{ varName,
								 interval.Right() }} );

	return ( interval.Length() *
			 ( f_a + 4 * f_mid + f_b ) / 6 );
}

double halg::MonteCarloIntegr( halg::Function const * func,
                               std::string const & varName,
                               halg::Interval const & interval,
                               halg::uint frequency )
{
    /*double result = 0;
    for( halg::uint i = 0; i < frequency; ++i )
    {
        double x = halg::RandDouble( interval.Left( ),
                                     interval.Right( ) );
        double y = func->Value( {{ varName, x }} );
        result += y;
    }*/

    double step = interval.Length( ) / frequency;
    double result = 0;
    for( double left = interval.Left(),
                right = left + step;
         right <= interval.Right( ) + step/2;
         left = right, right += step )
    {
        result += func->Value( {{ varName, left }} );
    }

    return result / frequency;
}
