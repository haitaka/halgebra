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

