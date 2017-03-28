import QtQuick 2.0
import QtQuick.Layouts 1.2
import "./../style"

/*!

  \class TextureManagerElement

  \brief Basic GUI element of the texture manager. Contains contents and a title

  */

ColumnLayout {

    id: root
    spacing: 2
    property string title: ""
    default property alias content: defaultContent.children;

    TitleText {

        text: root.title
        Layout.alignment: Qt.AlignHCenter

    }

    Item {

        id: defaultContent
        //always fill all the possible space given to it
        Layout.fillHeight: true
        Layout.fillWidth: true

        TextureManagerColumnComponent {

            id: defaultComponent

        }

    }

}







