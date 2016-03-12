import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

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

    //todo: fix
    ListModel{

        id: myListModel
        objectName: "myListModel"

        property string idString: "myListModel"

        ListElement{foo: "beep"}
        ListElement{foo: "boop"}

    }

    Rectangle {

        id: myRectangle
        objectName: "myRectangle"

        property string idString: "myRectangle"

        anchors.centerIn: parent

        Text {
            id: myTest
            objectName: "myTest"

            property string idString: "myTest"
            text: qsTr("Hello World")
            data: { text: "inner text" }
            anchors.centerIn: parent
            //anchors.verticalCenter: parent.anchors.verticalCenter

        }

    }



    Component.onCompleted: {

        //note: useObject name, it will print out conveniently to the console... :)

        //prettyPrintQMLObject(myTest, "derp");
        //console.log(JSON.stringify(myTest));
        //prettyPrintQMLObjectPropertiesOfType(myTest, "number", "derp");
        //printQmlObjectData(myTest, "derp");
        //prettyPrintLayoutProperties(myTest, "heading!!");
        //printQmlObjectProperties(myTest, ["width", "height"], "heading!!!!");
        //qmlPrintAll(myTest, "woohoo!")
        //console.log("idSTring: ", myTest.idString);
        //console.log("parent id string: ", myTest.parent.idString);
        //qmlPrintAllWithIdString(myTest, "heading!");
        //printParentIdString(myTest);
        //qmlPrintAnchors(myTest, "tttttt");

        //qmlPrintAll(myListModel, "heading");

        //prettyPrintQMLObject(myRectangle, "heading");

        //printQmlObjectProperties(myTest, ["height", "width", "visible", "anchors.centerIn"], "derp");

        //var thing = {one: "one", two: {twotwo: "twotwo", threethree: "threethree"}};

        //console.log(JSON.stringify(thing, null, "     "));

        printAllVarsInFunction(functionWithSomeVarsInIt, "printing some function");


    }

    function functionWithSomeVarsInIt(){

        var never = "gonna";
        var give = "you";
        var you = "up";
        var let = "you";
        var you = "down";

        return "boop";

    }

    function printAllVarsInFunction(functionObject, optionalHeading){

        //is optionalHeading not set, will be set to zero
        optionalHeading = optionalHeading || "";

        var outputString = "";

        if(optionalHeading !== ""){

            outputString += optionalHeading + ":\n"

        }


        console.log(functionObject);
        for(currentVar in functionObject){

            console.log("currentVar", currentVar);
             outputString += currentVar.toString() + "(" + typeof(currentVar) + "): " + functionObject[currentVar];

            //var map = new Map(Object.entries(functionObject));
            //outputString += map.toString();

        }

        console.log(outputString);

    }

    /*
      does not print qml objects, only plain old javascript objects
      */
    function prettyPrintObject(){

        console.log(JSON.stringify(thing, null, "     "));

    }

    /*!

      \fn prettyPrintQMLObject(objectToPrint, optionalHeading)

      \brief prints every property of a qml object passed to it on a separate line

     * params:
     * objectToPrint: a QML object of any type
     * optionalHeading: a string to be printed above the output. (Really useful if you want
     * to cntrl + f a bunch of log output)
     */
   function prettyPrintQMLObject(objectToPrint, optionalHeading){

       var outputString = getPrettyOutputStringForQMLObject(objectToPrint, optionalHeading);
       console.log(outputString);

   }

   function getPrettyOutputStringForQMLObject(qmlObject, optionalHeading){

       //is optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       //Object.



       for(var currentProperty in qmlObject){

           //if(currentProperty.toString() === 'data'){
           //     outputString += "\t\t" + getPrettyOutputStringForQMLObject(currentProperty);
           //}

           if(typeof(qmlObject[currentProperty]) !== "function"){

               outputString += currentProperty +  "(" + typeof(qmlObject[currentProperty]) + "): " + qmlObject[currentProperty] + "\n";

           }

       }

       return outputString;

   }

   /*
    * note: typeToPrint must be entered as string.
    * Acceptable typeToPrint arguments are any string that would be returned by the javascript typof() function.
    * examples you would commonly use: 'object', 'string', 'number', 'boolean', 'function'
    */
   function prettyPrintQMLObjectPropertiesOfType(qmlObject, typeToPrint, optionalHeading){

       var outputString = getPrettyOutputStringForQMLObjectPropertiesOfType(qmlObject, typeToPrint, optionalHeading);
       console.log(outputString);

   }

   function getPrettyOutputStringForQMLObjectPropertiesOfType(qmlObject, typeToPrint, optionalHeading){

       //is optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       for(var currentProperty in qmlObject){

           //if(currentProperty.toString() === 'data'){
           //     outputString += "\t\t" + getPrettyOutputStringForQMLObject(currentProperty);
           //}

           var currentPropertyType = typeof(qmlObject[currentProperty]);
           //console.log(currentPropertyType);
           if(currentPropertyType === typeToPrint){

               outputString += currentProperty +  "(" + typeof(qmlObject[currentProperty]) + "): " + qmlObject[currentProperty] + "\n";

           }

       }

       return outputString;

   }

   /*
     * this doesn't work and is totally stupid, but I'm keeping it here for now until I figure out if I want to delete it
     */
   function printQmlObjectData(qmlObject, optionalHeading){

       //is optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       for(var currentProperty in qmlObject){

           //if(currentProperty.toString() === 'data'){
           //     outputString += "\t\t" + getPrettyOutputStringForQMLObject(currentProperty);
           //}

           var currentPropertyType = typeof(qmlObject[currentProperty]);
           //console.log(currentPropertyType);
           if(currentProperty === "data"){

               outputString += currentProperty +  "(" + typeof(qmlObject[currentProperty]) + "): " + JSON.stringify(qmlObject[currentProperty], null, " ") + "\n";

           }

       }

       console.log(outputString);

   }

   function prettyPrintLayoutProperties(qmlObject, optionalHeading){

       //if optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       var layoutProperties = ["x", "y", "z", "width", "height"];

       for(var currentProperty in qmlObject){

           if(layoutProperties.indexOf(currentProperty) > -1){

                outputString += currentProperty + ": " + qmlObject[currentProperty] + "\n";

           }

       }

       console.log(outputString);

   }

   function printQmlObjectProperties(qmlObject, propertyList, optionalHeading){

       //if optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       for(var currentProperty in qmlObject){

           if(propertyList.indexOf(currentProperty) > -1){

                outputString += currentProperty + ": " + qmlObject[currentProperty] + "\n";

           }

       }

       console.log(outputString);

   }

   function printParentIdString(qmlObject){

       console.log(qmlObject.parent.idString);

   }

   /*
    * prints all the defined anchors that have been defined for the object passed,
    * if they have idString defined it will print idString, otherwise it will just print the object address as usual
    */
   function qmlPrintAnchors(qmlObject, optionalHeading){

       //if optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       var anchorNames = [

                   "anchors.baseline",
                   "anchors.bottom",
                   "anchors.centerIn",
                   "anchors.fill",
                   "anchors.horizontalCenter",
                   "anchors.left",
                   "anchors.right",
                   "anchors.top",
                   "anchors.verticalCenter",
                   "parent"

               ];

       var possibleAnchors = [

                   qmlObject.anchors.baseline,
                   qmlObject.anchors.bottom,
                   qmlObject.anchors.centerIn,
                   qmlObject.anchors.fill,
                   qmlObject.anchors.horizontalCenter,
                   qmlObject.anchors.left,
                   qmlObject.anchors.right,
                   qmlObject.anchors.top,
                   qmlObject.anchors.verticalCenter,
                   qmlObject.parent

               ];

       outputString += "{\n";
       for(var currentAnchor in possibleAnchors){

           console.log("current anchor: ", possibleAnchors[currentAnchor]);

           if(possibleAnchors[currentAnchor]){

               if(possibleAnchors[currentAnchor].idString){
                    outputString += anchorNames[currentAnchor] + ": " + possibleAnchors[currentAnchor].idString + "\n";
               }
               else{
                    outputString += anchorNames[currentAnchor] + ": " + possibleAnchors[currentAnchor] + "\n";
               }

           }

       }
       outputString += "}\n";
       console.log(outputString);

   }

   /*
     * this function assumes that you have put a property called "idString" in all your objects.
     * eg. property string idString.
     * this cloogy hack is a workaround the fact that the id property cannot be accessed. (I'm not sure what would have been
     * wrong with making it a read only property but whatever...
     *
     * still needs work, throws exception if idString is not defined
     */
   function qmlPrintAllWithIdStringBroken(qmlObject, optionalHeading){

       //if optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       var properties = {
                   'activeFocus': qmlObject.activeFocus,
                   'activeFocusOnTab': qmlObject.activeFocusOnTab,
                   'anchors.alignWhenCentered': qmlObject.anchors.alignWhenCentered,
                   'anchors.baseline': qmlObject.anchors.baseline.idString,
                   'anchors.baselineOffset': qmlObject.anchors.baselineOffset,
                   'anchors.bottom': qmlObject.anchors.bottom.idString,
                   'anchors.bottomMargin': qmlObject.anchors.bottomMargin.idString,
                   'anchors.centerIn': qmlObject.anchors.centerIn.idString,
                   'anchors.fill': qmlObject.anchors.fill.idString,
                   'anchors.horizontalCenter': qmlObject.anchors.horizontalCenter.idString,
                   'anchors.horizontalCenterOffset': qmlObject.anchors.horizontalCenterOffset.idString,
                   'anchors.left': qmlObject.anchors.left.idString,
                   'anchors.leftMargin': qmlObject.anchors.leftMargin,
                   'anchors.margins': qmlObject.anchors.margins,
                   'anchors.right': qmlObject.anchors.right.idString,
                   'anchors.rightMargin': qmlObject.anchors.rightMargin,
                   'anchors.top': qmlObject.anchors.top.idString,
                   'anchors.topMargin': qmlObject.anchors.topMargin,
                   'anchors.verticalCenter': qmlObject.anchors.verticalCenter.idString,
                   'anchors.verticalCenterOffset': qmlObject.anchors.verticalCenterOffset,
                   'antialiasing': qmlObject.antialiasing,
                   'baselineOffset': qmlObject.baselineOffset,
                   'children': qmlObject.children.idString,
                   'childrenRect.height': qmlObject.childrenRect.height,
                   'childrenRect.width': qmlObject.childrenRect.width,
                   'childrenRect.x': qmlObject.childrenRect.x,
                   'childrenRect.y': qmlObject.childrenRect.y,
                   'clip': qmlObject.clip,
                   'data': qmlObject.data.idString,
                   'enabled': qmlObject.enabled,
                   'focus': qmlObject.focus,
                   'height': qmlObject.height,
                   'implicitHeight': qmlObject.implicitHeight,
                   'implicitWidth': qmlObject.implicitWidth,
                   'layer.effect': qmlObject.layer.effect,
                   'layer.enabled': qmlObject.layer.enabled,
                   'layer.format': qmlObject.layer.format,
                   'layer.mipmap': qmlObject.layer.mipmap,
                   'layer.samplerName': qmlObject.layer.samplerName,
                   'layer.smooth': qmlObject.layer.smooth,
                   'layer.sourceRect': qmlObject.layer.sourceRect,
                   'layer.textureSize': qmlObject.layer.textureSize,
                   'layer.wrapMode': qmlObject.layer.wrapMode,
                   'opacity': qmlObject.opacity,
                   'parent': qmlObject.parent.idString,
                   'resources': qmlObject.resources,
                   'rotation': qmlObject.rotation,
                   'scale': qmlObject.scale,
                   'smooth': qmlObject.smooth,
                   'state': qmlObject.state,
                   'states': qmlObject.states,
                   'transform': qmlObject.transform,
                   'transformOrigin': qmlObject.transformOrigin,
                   'transitions': qmlObject.transitions,
                   'visible': qmlObject.visible,
                   'visibleChildren': qmlObject.visibleChildren,
                   'width': qmlObject.width,
                   'x': qmlObject.x,
                   'y': qmlObject.y,
                   'z': qmlObject.z
               };

       outputString += "{\n";
       for(var currentProperty in properties){

           //print out if currentProperty is truthy (otherwise we get a null pointer error)
           if(properties[currentProperty]){

               outputString += currentProperty + " (" + typeof(currentProperty) + "): " + properties[currentProperty] + "\n";

           }

       }
       outputString += "}\n";

       console.log(outputString);

   }

   function qmlPrintAll(qmlObject, optionalHeading){

       //if optionalHeading not set, will be set to zero
       optionalHeading = optionalHeading || "";

       var outputString = "";

       if(optionalHeading !== ""){

           outputString += optionalHeading + ":\n"

       }

       var properties = {
                   'activeFocus': qmlObject.activeFocus,
                   'activeFocusOnTab': qmlObject.activeFocusOnTab,
                   'anchors.alignWhenCentered': qmlObject.anchors.alignWhenCentered,
                   'anchors.baseline': qmlObject.anchors.baseline,
                   'anchors.baselineOffset': qmlObject.anchors.baselineOffset,
                   'anchors.bottom': qmlObject.anchors.bottom,
                   'anchors.bottomMargin': qmlObject.anchors.bottomMargin,
                   'anchors.centerIn': qmlObject.anchors.centerIn,
                   'anchors.fill': qmlObject.anchors.fill,
                   'anchors.horizontalCenter': qmlObject.anchors.horizontalCenter,
                   'anchors.horizontalCenterOffset': qmlObject.anchors.horizontalCenterOffset,
                   'anchors.left': qmlObject.anchors.left,
                   'anchors.leftMargin': qmlObject.anchors.leftMargin,
                   'anchors.margins': qmlObject.anchors.margins,
                   'anchors.right': qmlObject.anchors.right,
                   'anchors.rightMargin': qmlObject.anchors.rightMargin,
                   'anchors.top': qmlObject.anchors.top,
                   'anchors.topMargin': qmlObject.anchors.topMargin,
                   'anchors.verticalCenter': qmlObject.anchors.verticalCenter,
                   'anchors.verticalCenterOffset': qmlObject.anchors.verticalCenterOffset,
                   'antialiasing': qmlObject.antialiasing,
                   'baselineOffset': qmlObject.baselineOffset,
                   'children': qmlObject.children,
                   'childrenRect.height': qmlObject.childrenRect.height,
                   'childrenRect.width': qmlObject.childrenRect.width,
                   'childrenRect.x': qmlObject.childrenRect.x,
                   'childrenRect.y': qmlObject.childrenRect.y,
                   'clip': qmlObject.clip,
                   'data': qmlObject.data,
                   'enabled': qmlObject.enabled,
                   'focus': qmlObject.focus,
                   'height': qmlObject.height,
                   'implicitHeight': qmlObject.implicitHeight,
                   'implicitWidth': qmlObject.implicitWidth,
                   'layer.effect': qmlObject.layer.effect,
                   'layer.enabled': qmlObject.layer.enabled,
                   'layer.format': qmlObject.layer.format,
                   'layer.mipmap': qmlObject.layer.mipmap,
                   'layer.samplerName': qmlObject.layer.samplerName,
                   'layer.smooth': qmlObject.layer.smooth,
                   'layer.sourceRect': qmlObject.layer.sourceRect,
                   'layer.textureSize': qmlObject.layer.textureSize,
                   'layer.wrapMode': qmlObject.layer.wrapMode,
                   'opacity': qmlObject.opacity,
                   'parent': qmlObject.parent,
                   'resources': qmlObject.resources,
                   'rotation': qmlObject.rotation,
                   'scale': qmlObject.scale,
                   'smooth': qmlObject.smooth,
                   'state': qmlObject.state,
                   'states': qmlObject.states,
                   'transform': qmlObject.transform,
                   'transformOrigin': qmlObject.transformOrigin,
                   'transitions': qmlObject.transitions,
                   'visible': qmlObject.visible,
                   'visibleChildren': qmlObject.visibleChildren,
                   'width': qmlObject.width,
                   'x': qmlObject.x,
                   'y': qmlObject.y,
                   'z': qmlObject.z
               };

       outputString += "{\n";
       for(var currentProperty in properties){

           outputString += currentProperty + " (" + typeof(currentProperty) + "): " + properties[currentProperty] + "\n";

       }
       outputString += "}\n";

       console.log(outputString);

   }

}
