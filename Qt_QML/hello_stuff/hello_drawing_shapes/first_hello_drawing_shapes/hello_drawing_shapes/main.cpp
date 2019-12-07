#include "customwidgetv2.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QScopedPointer<CustomWidgetV2> customWidget( new CustomWidgetV2());

    customWidget->show();

    return a.exec();

}
