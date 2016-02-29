import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import "./style"

/*!

  \class TextureManager
  \brief the TextureManager can be used to import new textures, delete existing textures as well as
  manage texture categories.


  \reentrant

  The TextureManager is a self contained dialog window.

  Form and Function:

      Categories Column:
          In the texture manager there is a column for categories containing the current set of categories
          and a button that allows the user to add new categories.  Example categories might be: Nature, Urban
          etc.  A user may want to store all their textures in logical groups that make sense and that is the
          purpose of allowing the user to manage their categories in this column.  The user cannot delete any
          of the categories that came with their software product.

     Textures Column:
         In the texture manager there is a column for textures containing the current set of textures for the
         current selected category.  The textures will display as thumbnails.  There is an import button that
         will allow the user to import new textures into that selected category if they desire.


    Close Button:
        closes the texture manager


 */

Dialog {

    width: 546
    height: 460
    title: "Texture Manager"

    //Background rectangle:
    //contains the categories column and the textures column
    contentItem: Rectangle {

        id: root
        anchors.fill: parent
        color: "#3F4141"

        RowLayout {

            anchors.fill: parent
            spacing: 2

            /*
            ColumnLayout {

                Text {
                    text: "text"
                }

                Rectangle {

                    color: "red"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    border.color: "#000000"
                    border.width: 1
                }

            }



            Rectangle {

                color: "red"
                Layout.fillWidth: true
                Layout.fillHeight: true
                border.color: "#000000"
                border.width: 1
            }
            */



            //Categories List
            TextureManagerElement {

                id: categoryList
                anchors.top: parent.top
                anchors.left: parent.left
                //title.text: "Categories"

            }

            //Texture Gallery
            TextureManagerElement {

                id: textureGallery
            }



        }
    }


}
