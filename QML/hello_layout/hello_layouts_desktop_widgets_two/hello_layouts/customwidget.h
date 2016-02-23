#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QApplication>
#include <QListWidgetItem>
#include <QPushButton>
#include <QWidget>
#include <qboxlayout.h>


class CustomWidget : public QWidget
{
    //Meta Object Compiler finds this macro and then creates all the meta object code
    //that makes this a QT project and not just a C++ project
    Q_OBJECT

public:

    explicit CustomWidget(QWidget *parent = 0, QApplication *qApp = 0);

private slots:
    void itemClicked(QListWidgetItem *item);
    void updateItem();

signals:

private:

    //parent widget
    QWidget* parent;

    //hosting application
    QApplication* qApp;

    //a vertical layout that will hold all our widgets
    QVBoxLayout* layout;

    //this will display the cities
    QListWidget* m_list_widget;

    QLineEdit* m_edit;
    QPushButton* m_button;

    //the list of city names that our list widget will hold
    QStringList cities;

    //inits all the widgets and adds them to the layout
    void initLayout();

    void initCities();
    void addCitiesToListWidget();

    void connectWidgetsToEventListeners();

};

#endif // CUSTOMWIDGET_H
