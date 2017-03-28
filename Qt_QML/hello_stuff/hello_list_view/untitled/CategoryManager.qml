import QtQuick 2.0
import QtQuick.Layouts 1.2


Rectangle {

    anchors.fill: parent
    Layout.fillHeight: true
    Layout.fillWidth: true

    ListView {

        id: categoryManagerListView
        anchors.fill: parent
        clip: true

        model: ListModel {
            id: nameModel
            ListElement {name: "never"}
            ListElement {name: "gonna"}
            ListElement {name: "give"}
            ListElement {name: "you"}
            ListElement {name: "up"}

        }

        delegate: Component {
            id: nameDelegate
            Rectangle {
                Layout.fillWidth: true
                height: 10
                color: "blue"
                Text {
                    text: name
                }
            }

        }

    }


}
