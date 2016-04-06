#pragma once

#include <QWidget>
#include <QPainter>
#include <QColor>
#include "../Utils.h"

namespace halg
{
class Ploter;
class Axis : public QWidget
{
    Q_OBJECT
public:
	explicit Axis( Ploter & ploter, QColor color,
				   QWidget * parent = 0 )
		: QWidget( parent )
		, m_ploter( ploter )
		, m_color( color )
		, m_minPoint( 1 )
	{}

	void paintEvent( QPaintEvent * )
	{
		QPainter painter( this );
		painter.setPen( m_color );

		DrawOX( painter );
		DrawOY( painter );
	}

	void DrawOX( QPainter & painter );
	void DrawOY( QPainter & painter );

	void SetScalePoint( double value )
	{
		m_minPoint = value;
	}

private:
    Ploter & m_ploter;
    QColor m_color;
	double m_minPoint;

    static const int MIN_WIDTH;
    static const int MAJ_WIDTH;
};
}
