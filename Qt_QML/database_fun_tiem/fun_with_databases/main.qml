import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.LocalStorage 2.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    DataBaseController {
        id: myDatabaseController
        objectName: "myDatabaseController_main_fun_with_databases"
        Component.onCompleted:
        {
            var path = myDatabaseController.getOfflineStoragePath();
            console.log("offline storage path: " + path);
        }
    }
}
