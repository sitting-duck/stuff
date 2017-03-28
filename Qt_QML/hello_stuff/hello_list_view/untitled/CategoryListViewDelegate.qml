import QtQuick 2.0
import QtQuick.Layouts 1.2

Repeater {

    property var currentModel

    id: root
    model: currentModel

    Rectangle {

        property string text

        Layout.fillWidth: true
        height: 25
        color: "blue"

        Text {

            text: currentModel.name
            font.pixelSize: 14

        }

    }

}



