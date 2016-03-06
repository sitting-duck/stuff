#include "customwidget.h"
#include "mainwindow.h"
#include <QApplication>

/*
 *
 * This program will update the location of a yellow rectangle to a new location every time the user
 * clicks.
 *
 */
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();

    QApplication app(argc, argv);

    //this QScopedPointer type makes sure out CustomWidget gets deleted when it goes out of scope
    QScopedPointer<QWidget> widget(new CustomWidget());

    widget->resize(240, 120);
    widget->show();
    return app.exec();
}
