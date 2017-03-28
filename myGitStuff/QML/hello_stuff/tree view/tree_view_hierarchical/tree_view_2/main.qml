import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls 1.4

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

    Label {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    TreeView {
            anchors.fill: parent
            model: theModel
            itemDelegate: Rectangle {
               color: ( styleData.row % 2 == 0 ) ? "white" : "lightblue"
               height: 20

               Text {
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.left: parent.left // by default x is set to 0 so this had no effect
                   text: styleData.value
               }
           }

            TableViewColumn {
                role: "name_role"
                title: "Name"


            }
            TableViewColumn {
                role: "description_role"
                title: "Description"
            }

            itemDelegate: Item {
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            color: styleData.textColor
                            elide: styleData.elideMode
                            text: styleData.value
                        }
            }

            Component.onCompleted: {
                      model.append({"name":"Never"})
                      model.append({"name":"gonna"})
                      model.append({"name":"give"})
                      model.append({"name":"you"})
                      model.append({"name":"up"})
                      model.append({"name":"Never"})
                      model.append({"name":"gonna"})
                      model.append({"name":"let"})
                      model.append({"name":"you"})
                      model.append({"name":"down"})
                  }
    }
}
