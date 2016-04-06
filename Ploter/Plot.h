#pragma once

#include <QColor>
#include <map>

#include "../Function.h"

namespace halg
{
class Plot
{
public:
	Plot( double xMin, double xMax,
		  double yMin, double yMax,
		  QColor color )
		: m_xMin( xMin )
		, m_xMax( xMax )
		, m_yMin( yMin )
		, m_yMax( yMax )
		, m_color( color )
	{}
	Plot( Plot const & src )
		: m_xMin( src.m_xMin )
		, m_xMax( src.m_xMax )
		, m_yMin( src.m_yMin )
		, m_yMax( src.m_yMax )
		, m_color( src.m_color )
	{}

	virtual double GetVal( double x ) const = 0;

	QColor const & GetColor()const
	{
		return m_color;
	}
	double GetXMin() const
	{
		return m_xMin;
	}
	double GetXMax() const
	{
		return m_xMax;
	}
	double GetYMin() const
	{
		return m_yMin;
	}
	double GetYMax() const
	{
		return m_yMax;
	}

private:
	double m_xMin;
	double m_xMax;
	double m_yMin;
	double m_yMax;
	QColor m_color;
};


class FuncPlot : public Plot
{
public:
	FuncPlot( double xMin, double xMax,
			  double yMin, double yMax,
			  QColor color,
			  halg::Function const * func,
			  std::string varName )
		: Plot( xMin, xMax, yMin, yMax, color )
		, m_func( func->Copy( ) )
		, m_varName( varName )
	{}
	double GetVal( double x ) const override
	{
		return m_func->Value( {{ m_varName, x }} );
	}
private:
	halg::Function * m_func;
	std::string m_varName;
};

class PieceConstPlot : public Plot
{
public:
	PieceConstPlot( double xMin, double xMax,
					double yMin, double yMax,
					QColor color,
					std::map< double, double > const & grid )
		: Plot( xMin, xMax, yMin, yMax, color )
		, m_grid( grid )
	{}
	PieceConstPlot( double xMin, double xMax,
					double yMin, double yMax,
					QColor color,
					std::vector< double > const & values )
		: Plot( xMin, xMax, yMin, yMax, color )
	{
		double step = ( ( xMax - xMin ) / values.size( ) );
		double x = xMin;
		for( auto val : values )
		{
			m_grid[ x ] = val;
			x += step;
		}
	}
	double GetVal( double x ) const override
	{
		return (--m_grid.upper_bound( x ))->second;
	}
private:
	std::map< double, double > m_grid;
};

class PieceLinPlot : public Plot
{
public:
	PieceLinPlot( double xMin, double xMax,
				  double yMin, double yMax,
				  QColor color,
				  std::map< double, double > const & grid )
		: Plot( xMin, xMax, yMin, yMax, color )
		, m_grid( grid )
	{}
	PieceLinPlot( double xMin, double xMax,
				  double yMin, double yMax,
				  QColor color,
				  std::vector< double > const & values )
		: Plot( xMin, xMax, yMin, yMax, color )
	{
		double step = ( ( xMax - xMin ) / values.size( ) );
		double x = xMin;
		for( auto val : values )
		{
			m_grid[ x ] = val;
			x += step;
		}
	}
	double GetVal( double x ) const override
	{
		auto nextNode = m_grid.upper_bound( x );
		double xLeft = std::prev(nextNode)->first;
		double yLeft = std::prev(nextNode)->second;
		double xRight = (nextNode)->first;
		double yRight = (nextNode)->second;
		if( nextNode == m_grid.end() )
		{
			return yLeft;
		}

		return ( yLeft +
				 ( x - xLeft ) / ( xRight - xLeft ) *
				 ( yRight - yLeft ) );
	}
private:
	std::map< double, double > m_grid;
};

template< typename FuncType >
class TmplFuncPlot : public Plot
{
public:
	TmplFuncPlot( double xMin, double xMax,
				  double yMin, double yMax,
				  QColor color,
				  FuncType const & func )
		: Plot( xMin, xMax, yMin, yMax, color )
		, m_func( func )
	{}
	double GetVal( double x ) const override
	{
		return m_func( x );
	}
private:
	FuncType m_func;
};
}
