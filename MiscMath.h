#pragma once

#include <cmath>
#include <string>
#include <map>
#include <unordered_map>

namespace halg
{
	const double PI = acos( -1 );
	const double GOLD_RATIO = ( sqrt( 5 ) + 1 ) / 2;

	typedef std::unordered_map< std::string, double >
			VarVals;

	class Interval
	{
	public:
		Interval( )
			: m_left( 0 )
			, m_right( 0 )
		{ }
		Interval( double left, double right )
			: m_left( left )
			, m_right( right )
		{ }
		Interval( Interval const & src )
			: m_left( src.m_left )
			, m_right( src.m_right )
		{ }

		double Left( ) const
		{
			return m_left;
		}
		double Right( ) const
		{
			return m_right;
		}
		double Length( ) const
		{
			return fabs( m_right - m_left );
		}
		double Mid( ) const
		{
			return ( m_right + m_right ) / 2;
		}

		//operator std::string ( ) const;

		bool operator < ( Interval const & right ) const
		{
			if (m_left <= right.m_right)
			{
				if ( m_left != right.m_left ) return true;
				else return Length( ) < right.Length( );
			}
			return false;
		}
	private:
		double m_left;
		double m_right;
	};
}
