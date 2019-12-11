import QtQuick 2.0
import QtQuick.Layouts 1.2

ColumnLayout {

    id: root
    spacing: 2
    property string title: ""

    TitleText {
        Layout.alignment: Qt.AlignHCenter

    }

    Item {

        id: defaultContent
        //always fill all the possible space given to it
        Layout.fillHeight: true
        Layout.fillWidth: true

        ColumnComponent {
        }

    }

}

