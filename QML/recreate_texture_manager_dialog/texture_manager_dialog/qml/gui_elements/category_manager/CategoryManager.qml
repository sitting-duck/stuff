import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "./../"
import "./../../style"

TextureManagerColumn {

    title: "Categories"

    content: TextureManagerColumnComponent {

        //color: "red"

        ScrollView {

            anchors.fill: parent
            style: TextureManagerScrollView
            clip: true

            ColumnLayout {

                anchors.fill: parent

                ListView {

                    id: ctegoryListView
                    //model: ???


                }
            }


        }


    }
}
