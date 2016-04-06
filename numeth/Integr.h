#pragma once

/* Trapez precision O(h^5)
 * Simpson precision O(h^5)
 */

#include <string>

#include "../Function.h"
#include "../MiscMath.h"
#include "../Utils.h"
#include <functional>

namespace halg
{
	struct TrapezRule
	{
		double operator () (
				halg::Function const * func,
				std::string const & varName,
				halg::Interval const & interval
			) const;
	};
	struct SimpsonRule
	{
		double operator () (
				halg::Function const * func,
				std::string const & varName,
				halg::Interval const & interval
			) const;
	};


	template< class IntegrRule >
	double QuadrIntegr( halg::Function const * func,
						std::string const & varName,
						halg::Interval const & interval,
						halg::uint frequency )
	{
		double step = interval.Length( ) / frequency;
		double result = 0;
		for( double left = interval.Left(),
					right = left + step;
			 right <= interval.Right( ) + step/2;
			 left = right, right += step )
		{
			result += halg::SimpsonRule( )(
						  func, varName,
						  halg::Interval( left, right )
					  );
		}
		return result;
	}
}
