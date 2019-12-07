import QtQuick 2.5

Rectangle {
    property alias mouseArea: mouseArea

    width: 800
    height: 800

    MouseArea {
        id: mouseArea
        width: 800
        height: 800
        anchors.fill: parent

        BorderImage {
            id: borderImage1
            width: 800
            height: 800
            anchors.fill: parent
            source: "pictures/think_twice_code_once-wallpaper-2048x1152.jpg"
        }

        Column {
            width: 200; height: 200

            TextInput {id: myTextInput; text: "Editable Text" }

            Text { text: myTextInput.text }

            ListView {
                id: listView1
                x: 0
                y: 0
                width: 240
                height: 800
                flickableDirection: Flickable.VerticalFlick
                orientation: ListView.Vertical
                spacing: 5
                highlightRangeMode: ListView.ApplyRange
                flickDeceleration: 1499
                contentWidth: 0
                clip: false
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }

                delegate: Item {
                    x: 5
                    width: 80
                    height: 40
                    Row {
                        id: row1
                        Rectangle {
                            width: 40
                            height: 40
                            color: colorCode
                        }

                        Text {
                            text: name
                            font.bold: true
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 10
                    }
                }
            }
        }
    }
}
