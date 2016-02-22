#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QListWidgetItem>
#include <QPushButton>
#include <QWidget>


class CustomWidget : public QWidget
{
    //Meta Object Compiler finds this macro and then creates all the meta object code
    //that makes this a QT project and not just a C++ project
    Q_OBJECT

public:

    explicit CustomWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void itemClicked(QListWidgetItem *item);
    void updateItem();

signals:

private:
    QPoint m_lastPos;
    QListWidget* m_widget;
    QLineEdit* m_edit;
    QPushButton* m_button;

    //updates the location of the yellow rectangle
    void drawYellowRectangleInMainRectangle(QRect &mainRectangle);
};

#endif // CUSTOMWIDGET_H
