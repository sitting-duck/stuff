import QtQuick 2.0
import QtQuick.Dialogs 1.2


/*!

  \class TextureManager
  \brief the TextureManager can be used to import new textures, delete existing textures as well as
  manage texture categories.

  \ingroup Dialog

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

    Rectangle {

        width: parent.width
        height: parent.height
        color: "#3F4141"
    }


}
