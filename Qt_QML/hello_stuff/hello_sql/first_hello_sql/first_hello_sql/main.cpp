#include "mainwindow.h"
#include <QApplication>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStringListModel>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTableView* m_view = new QTableView();
    //QStringListModel* m_model = new QStringListModel();
    //m_view->setModel(m_model);

    //let's make a database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cities.db");

    if(!db.open()){
        qFatal("unable to open datbase");
    }

    QSqlTableModel* m_model = &QSqlTableModel();
    m_model->setTable("city");
    m_model->setHeaderData(0, Qt::Horizontal, "City");
    m_model->setHeaderData(1, Qt::Horizontal, "Country");

    m_view->setModel(m_model);
    m_model->select();

    //for higher level of model operations QT provides a sort file proxy model, which
    //allows you in thebasic form to sort and filter another model
    QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(m_model);
    m_view->setModel(proxy);
    m_view->setSortingEnabled(true);

    w.show();

    return a.exec();
}
