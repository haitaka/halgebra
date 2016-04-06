#include "Axis.h"
#include "Ploter.h"

const int halg::Axis::MIN_WIDTH = 2;
const int halg::Axis::MAJ_WIDTH = 5;

void halg::Axis::DrawOX( QPainter & painter )
{
	int ox_top = m_ploter.GetYNull();
	if (ox_top < 0)
    {
		ox_top = 0;
    }
	else if (ox_top > geometry().height())
    {
        ox_top = geometry().height();
    }
	painter.drawLine(
        QPoint(geometry().x(),     ox_top),
        QPoint(geometry().width(), ox_top)
    );

	for(double x = floor(m_ploter.m_xMin / m_minPoint) * m_minPoint;
		x <= m_ploter.m_xMax + m_minPoint / 2;
		x += m_minPoint)
    {
        int width;
		int x_screen = m_ploter.GetScreenCoord(x, 0).x();

		if (halg::IsInt(x, m_minPoint / 2))
        {
            if (round(x) == 0)
            {
                width = 0;
            }
            else
            {
                width = MAJ_WIDTH;
                QString label = QString::number(round(x));
				painter.drawText(QPoint(x_screen - width,
                                  ox_top + width*4),
                           label);
            }
        }
        else
        {
            width = MIN_WIDTH;
        }
		painter.drawLine(
            QPoint(x_screen, ox_top - width),
            QPoint(x_screen, ox_top + width)
        );
    }
}


void halg::Axis::DrawOY(QPainter & painter)
{
	int oy_left = m_ploter.GetXNull();
    if (oy_left < 0)
    {
        oy_left = 0;
    }
    else if (oy_left > geometry().width())
    {
        oy_left = geometry().width();
    }
	painter.drawLine(
        QPoint(oy_left, geometry().y()),
        QPoint(oy_left, geometry().height())
    );

	for(double y = floor(m_ploter.m_yMin / m_minPoint) * m_minPoint;
		y <= m_ploter.m_yMax + m_minPoint / 2;
		y += m_minPoint)
    {
        int width;
		int y_screen = m_ploter.GetScreenCoord(0, y).y();

		if (halg::IsInt(y, m_minPoint / 2))
        {
            if (round(y) == 0)
            {
                width = 0;
            }
            else
            {
                width = MAJ_WIDTH;
                QString label = QString::number(round(y));
				painter.drawText(QPoint(oy_left - width*4,
                                  y_screen + 4),
                           label);
            }
        }
        else
        {
            width = MIN_WIDTH;
        }
		painter.drawLine(
            QPoint(oy_left - width, y_screen),
            QPoint(oy_left + width, y_screen)
        );
    }
}
