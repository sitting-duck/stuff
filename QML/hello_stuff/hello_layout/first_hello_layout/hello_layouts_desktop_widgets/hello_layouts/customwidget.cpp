#include "customwidget.h"

#include <QMouseEvent>
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //adjusted Returns a new rectangle with dx1, dy1, dx2 and dy2
    //added respectively to the existing coordinates of this rectangle.
    QRect mainRectangle = rect().adjusted(10, 10, -10, -10);

    //setPen(const QColor& color) sets the painter's pen to have style Gt::SolidLine, width 0, and the
    //specified color
    painter.setPen(QColor("#33B5E5"));

    //drawRect draws the given rectangle with the current pen and brush
    painter.drawRect(mainRectangle);

    drawYellowRectangleInMainRectangle(mainRectangle);

}

void CustomWidget::drawYellowRectangleInMainRectangle(QRect &mainRectangle){

    QPainter painter(this);

    QRect yellowRectangle(QPoint(0, 0), QSize(40, 40));
    if(m_lastPos.isNull()){

        //moveCenter(position) moves the rectange, leaving the center point at the given position
        yellowRectangle.moveCenter(mainRectangle.center());

    }else{

        yellowRectangle.moveCenter(m_lastPos);

    }
    painter.fillRect(yellowRectangle, QColor("#FFBB33"));

}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    //pos() returns the position of the mouse cursor relative to the widget that
    //received the event
    m_lastPos = event->pos();

    //does not cause an immediate repaint; instead it schedules a paint event for processing
    //whe QT returns to the main event loop.  This permits QT to optimize for more speed and less
    //flicker than a call to repaint() does
    update();
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
    update();
}

void CustomWidget::itemClicked(QListWidgetItem *item)
{

}

void CustomWidget::updateItem()
{

}
