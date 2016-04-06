#pragma once

#include <QtGlobal>
#include <QtMath>
#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <vector>

#include "Axis.h"
#include "Plot.h"

namespace halg
{
class Ploter : public QWidget
{
    Q_OBJECT

	friend class halg::Axis;
public:
	Ploter( double xMin, double xMax,
			double yMin, double yMax,
			QColor const & axisColor )
		: QWidget( nullptr )
		, m_xMin( xMin )
		, m_xMax( xMax )
		, m_yMin( yMin )
		, m_yMax( yMax )
		, m_axis( *this, axisColor, this )
	{
		setWindowTitle( tr( "Ploter" ) );
		resize( QSize( 640, 480 ) );
	}

	void AddPlot( Plot * plot )
	{
		m_plots.push_back( plot );
		update( );
	}

	halg::uint GetXNull() const
    {
		return m_xNull;
    }
	halg::uint GetYNull() const
    {
		return m_yNull;
    }
	QPoint GetScreenCoord( double x, double y ) const
	{
		return QPoint( ( ( x * m_scale ) + m_xNull ),
					   (-( y * m_scale ) + m_yNull ) );
	}

	void SetScalePoint( double value )
	{
		m_axis.SetScalePoint( value );
	}

	void DrawPlot( Plot const * plot );
	void paintEvent( QPaintEvent * );
	void resizeEvent( QResizeEvent * );
private:
	double m_xMin;
	double m_xMax;
	double m_yMin;
	double m_yMax;
	halg::uint m_xNull;
	halg::uint m_yNull;
	halg::uint m_scale;
	halg::Axis m_axis;
	std::vector< Plot * > m_plots;
};


class AnimPloter : public Ploter
{
    Q_OBJECT
public:
	AnimPloter( double xMin, double xMax,
				double yMin, double yMax,
				QColor axisColor,
				halg::uint delay )
		: Ploter( xMin, xMax, yMin, yMax, axisColor )
		, m_timer( this )
	{
		connect( &m_timer, SIGNAL( timeout( ) ),
				 this, SLOT( update( ) ) );
		m_timer.start( delay );
    }
	void AddAnimPlot( std::vector< Plot * > const & plotAnim )
    {
		m_animPlots.push_back( plotAnim );
		update( );
	}
	void paintEvent( QPaintEvent * event );
private:
	std::vector< std::vector< Plot * > > m_animPlots;
	halg::uint m_frameCount;
	QTimer m_timer;
};
}
