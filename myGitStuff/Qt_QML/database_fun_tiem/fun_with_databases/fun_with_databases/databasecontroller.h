#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QString>

/*
 * Author: Ashley Tharp
 * date created: 3/18/2016
 * */
class DatabaseController : public QObject
{

    Q_OBJECT

public:
    explicit DatabaseController (QObject* parent = 0) : QObject(parent) {}

    Q_INVOKABLE static QString getOfflineStoragePath();
};

#endif // DATABASECONTROLLER_H
