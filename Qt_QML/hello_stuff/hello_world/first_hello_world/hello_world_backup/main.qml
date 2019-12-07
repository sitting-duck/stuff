import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

       Rectangle {

           width: 200
           height: 100
           color: "red"

           Text {
               //qsTr mark this string for translation and makes our code international
               text: qsTr("Hello World")
               anchors.centerIn: parent
           }

       }


}
