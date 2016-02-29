import QtQuick 2.3
import QtQuick.Controls 1.2
import "./qml"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Example Project for Modular Texture Manager Dialog")

    
    //Menu Bar Options
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

    //inform user of the intention of this project
    Label {

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        text: qsTr("Example Project for Modular Texture Manager Dialog
    author: Ashley Tharp
    date: 2/26/2016
    Topaz Labs
    Objective: to create a standalone modular texture manager dialog
    that can be easily ported into all Topaz applications")

    }

    //button to open texture manager dialog where the user can browse categories and
    //select a texture to apply to their image
    Button {

        id: openTextureManagerButton
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        text: "Open Texture Manager"
        onClicked: {myTextureManager.open()}//todo: write dlgTextureManager.qml
        tooltip: qsTr("Open texture manager")
    }

    //allows the user to organize, import, and delete textures
    TextureManager {
        id: myTextureManager
    }

}
