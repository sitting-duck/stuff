import QtQuick 2.3
import QtQuick.Controls.Styles 1.2

ScrollViewStyle {

    //controls the appearance of the scroll bar background
    scrollBarBackground: Rectangle {

        implicitWidth: 12
        color: "#202020"

    }

    //controls the appearance of the scroll bar handle
    handle: Item {

        implicitWidth: 12
        implicitHeight: 26

        Rectangle {

            color: styleData.hovered? "#828282": "525252"
            radius: 6
            anchors.fill: parent
            anchors.topMargin: 1
            anchors.leftMargin: 1
            anchors.rightMargin: 1
            anchors.bottomMargin: 1

        }
    }

    //control the appearance of the increment buttons (the arrow buttons
    //at the top and bottom of the scroll bar)
    incrementControl: Item {}
    decrementControl: Item {}

}
