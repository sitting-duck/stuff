#include "databasecontroller.h"


/*
 * Author: Ashley Tharp
 * date created: 3/18/2016
 * */

DatabaseController::DatabaseController()
{


}

QString DatabaseController::getOfflineStoragePath()
{
    // The default is QML/OfflineStorage in the platform-standard user application data directory.
    return QQmlEngine::offlineStoragePath();

}
