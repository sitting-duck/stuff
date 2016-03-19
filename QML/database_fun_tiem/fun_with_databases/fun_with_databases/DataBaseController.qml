import QtQuick 2.0

/*!

  \qmltype DataBaseController

  \brief something

  */
Item {

    id: _top
    objectName: "_top"

    property var debug: {  "showSQLStatements" : false,
                           "showErrorOutput" : true,
                           "printDatabaseContents" : false
                        }

    /*

      \qmlmethod DatabaseController::getOfflineStoragePath()

      \brief returns the path of where all local data for the application will be stored.

      */
    function getOfflineStoragePath() {

        return QQmlEngine::offlineStoragePath();

    }

}

