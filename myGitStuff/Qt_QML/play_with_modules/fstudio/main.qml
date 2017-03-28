import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.2

//import "widgets/TextureManager"

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

        color: "red"
        anchors.fill: parent

        GridLayout {

            anchors.fill: parent
            rowSpacing: 3
            columnSpacing: 3
            flow: width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom

            Rectangle {

                color: "blue"
                Layout.fillHeight: true
                Layout.fillWidth: true

            }

            Rectangle {

                color: "blue"
                Layout.fillHeight: true
                Layout.fillWidth: true

            }


        }

        Label {
            text: qsTr("herp")
            anchors.centerIn: parent
        }

    }



}
