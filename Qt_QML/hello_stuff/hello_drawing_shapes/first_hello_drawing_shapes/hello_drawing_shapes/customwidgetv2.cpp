#include "customwidgetv2.h"

#include <QGraphicsRectItem>
#include <QVBoxLayout>

CustomWidgetV2::CustomWidgetV2(QWidget *parent) : QWidget(parent)
{

    //attach the scene to the view
    m_view = new QGraphicsView(this);
    m_scene = new QGraphicsScene(this);
    m_view->setScene(m_scene);

    //make a vertical box layout and add the view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_view);
    setLayout(layout);

    //add the rectangle to the scene
    QGraphicsRectItem* rect1 = m_scene->addRect(0,0, 40, 40, Qt::NoPen, QColor("#FFBB33"));
    rect1->setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsMovable);

}
