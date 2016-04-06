#include "Ploter.h"

void halg::Ploter::DrawPlot( Plot const * plot )
{
	QPainter painter(this);

	painter.setPen( plot->GetColor( ) );

	double x = plot->GetXMin();
	double val = plot->GetVal( x );
	double max = plot->GetXMax();
	double step = 1. / m_scale;
	while( x  < max )
	{
		double nextX = x + step;
		double nextVal = plot->GetVal( nextX );
		painter.drawLine(
					GetScreenCoord( x, val ),
					GetScreenCoord( nextX, nextVal )
				 );
		val = nextVal;
		x = nextX;
	}
}

void halg::Ploter::paintEvent( QPaintEvent * )
{
	for(auto plot: m_plots)
	{
		DrawPlot( plot );
	}
}

void halg::Ploter::resizeEvent( QResizeEvent * )
{
	m_scale = qMin(
		( geometry( ).width( ) / ( m_xMax - m_xMin ) ),
		( geometry( ).height( ) / ( m_yMax - m_yMin ) )
	);
	/*
	m_null_x = qMax(qFloor(m_scale * ( -m_xMin )),
					geometry().width() / 2);
	m_null_y = qMax(qFloor(m_scale * ( m_yMax )),
					geometry().height() / 2);
	*/
	m_xNull = qFloor(m_scale * ( -m_xMin ));
	m_yNull = qFloor(m_scale * ( m_yMax ));
	m_axis.resize( size( ) );
}

void halg::AnimPloter::paintEvent( QPaintEvent * event )
{
	if ( m_animPlots.empty( ) ) return;

	bool hasNewFrames = false;
	for (auto plotAnim : m_animPlots)
	{
		Plot * plot;
		if ( m_frameCount < plotAnim.size( ) )
		{
			plot = plotAnim[ m_frameCount ];
			hasNewFrames = true;
		}
		else
		{
			plot = plotAnim[ plotAnim.size( ) - 1 ];
		}
		DrawPlot( plot );
	}
	if ( hasNewFrames )
	{
		++m_frameCount;
	}
	else
	{
		m_timer.stop( );
	}
	Ploter::paintEvent( event );
}
