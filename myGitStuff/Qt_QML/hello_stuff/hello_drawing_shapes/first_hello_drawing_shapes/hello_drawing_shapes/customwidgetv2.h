#ifndef CUSTOMWIDGETV2_H
#define CUSTOMWIDGETV2_H

#include <QGraphicsView>
#include <QWidget>

class CustomWidgetV2 : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidgetV2(QWidget *parent = 0);

signals:

public slots:

private:
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
};

#endif // CUSTOMWIDGETV2_H
