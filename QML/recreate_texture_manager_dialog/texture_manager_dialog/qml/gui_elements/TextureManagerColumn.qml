import QtQuick 2.0
import QtQuick.Layouts 1.2
import "./style"

/*!

  \class TextureManagerElement

  \brief Basic GUI element of the texture manager. Contains contents and a title

  */


ColumnLayout {

    id: root
    spacing: 2
    property string title: ""

    TitleText {

        text: root.title
        Layout.alignment: Qt.AlignHCenter

    }

    Rectangle {

        radius: 3
        color: "#494b4b"
        border.color: "#000000"
        border.width: 1

        //always all the possible space given to it
        Layout.fillHeight: true
        Layout.fillWidth: true

        //leave a 10 pixel space around all elements
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10

    }
}





