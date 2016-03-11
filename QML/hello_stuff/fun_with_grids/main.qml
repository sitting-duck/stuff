import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.2

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

        id: background
        anchors.fill: parent
        color: "green"

        Column {

            id: categoryColumn
            height:background.height
            width: .5 * background.width
            anchors.top: background.top
            anchors.left: background.left

            Rectangle {

                id: categoryManager
                color: "purple"
                height:background.height
                width: .5 * background.width

            }

        }

        Column {

            id: galleryColumn
            height:background.height
            width: .5 * background.width
            anchors.top: background.top
            anchors.right: background.right

            Rectangle {

                id: gallery
                color: "blue"
                height: .5 * background.height
                width: .5 * background.width

                GridView {

                    height: gallery.height
                    width: .5 * background.width

                    cellHeight: 15
                    cellWidth: 15

                    model: 400

                    delegate: Rectangle {

                        color: "red"
                        height: 12
                        width: 12

                    }
                }

            }

            Rectangle {

                id: optionsBox
                color: "gray"
                height: .5 * background.height
                width: .5 * background.width

            }

        }

    }

}
