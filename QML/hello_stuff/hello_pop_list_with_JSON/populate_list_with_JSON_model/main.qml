import QtQuick 2.3
import QtQuick.Controls 1.2

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

    Rectangle {

        anchors.fill: parent


        ListView {

            id: categoryListView
            anchors.fill: parent
            clip: true

            model: [
                {"name": "Answer", "value": "42"},
                {"name": "Pastis", "value": "51"},
                {"name": "Alsace", "value": "67"},
                {"name": "Alsace", "value": "68"}
            ]

            delegate: Text {

                text: model.name

            }


        }

    }
}
