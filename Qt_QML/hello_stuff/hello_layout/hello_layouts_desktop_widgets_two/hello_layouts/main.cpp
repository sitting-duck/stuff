#include "customwidget.h"
#include "mainwindow.h"
#include <iostream>
#include <QApplication>

/*
 *
 * This program has a list of cities of which, when selected, their name can be edited in the box below.
 *
 */
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    //this QScopedPointer type makes sure out CustomWidget gets deleted when it goes out of scope
    QScopedPointer<QWidget> widget(new CustomWidget());

    widget->resize(240, 120);
    widget->show();
    return app.exec();
}
