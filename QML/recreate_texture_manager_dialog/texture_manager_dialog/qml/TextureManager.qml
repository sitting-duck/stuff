import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import "./gui_elements/category_manager"
import "./gui_elements/texture_gallery"

Dialog {




    title: "Texture Manager"
    width: 546
    height: 460

    contentItem: Rectangle {

        color: "#3F4141"
        anchors.fill: parent

        RowLayout {

            anchors.fill: parent
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            CategoryManager {

            }

            TextureGallery {

            }

        }

    }



}


