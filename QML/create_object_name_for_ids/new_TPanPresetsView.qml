import QtQuick 2.5

import QtQuick.Controls 1.4

import QtQuick.Controls.Styles 1.4

import QtQuick.Layouts 1.2

import QtQuick.Dialogs 1.2



import QtQml.Models 2.2



import TBase     1.0

import TControls 1.0

import TPresets  1.0



import "../TBase/TmConfigure.js" as TC



// TBD ---

// should move TPresetView and TPresetDelegate from TPresets folder to here

//    TPresets plugin will only contains controller



Rectangle {

 id: top
 objectName: "top"



    //  ============ interface ================

    property TEffect      teffect // IN

    property TMainActions actions // IN





    // ============= implementation ===========

    color: TC.colorPanel



    /*

    TToolBar {

 id: toolBar
 objectName: "toolBar"

        width: parent.width

        RowLayout {
                    id: RowLayout0
                    objectName: "RowLayout0"

            width: parent.width



            ComboBox {

 id: cbCategory
 objectName: "cbCategory"

                Layout.fillWidth: true

                //model: presetController.getCategories(true);



                onCurrentIndexChanged: {
                            id: onCurrentIndexChanged0
                            objectName: "onCurrentIndexChanged0"

                    //if (presetView) presetView.updatePreset()

                }

                style: PmComboBoxStyle {}
                             id: style0
                             objectName: "style0"



            }



            TToolButtonIcon {

 id: btPack
 objectName: "btPack"

                action: Action {
                             id: action0
                             objectName: "action0"

                    text: qsTr("Pack")

                    iconSource: "qrc:/TControls/icons/center-white.png"

                    onTriggered: {
                                id: onTriggered0
                                objectName: "onTriggered0"

                        presetPackList.popup()

                    }

                }



                //JSON object

                property var packQuery: ({text:'All'})
                              id: property0
                              objectName: "property0"

                onPackQueryChanged: {
                            id: onPackQueryChanged0
                            objectName: "onPackQueryChanged0"

                    // presetView.updatePreset()

                }



                Menu {

 id: presetPackList
 objectName: "presetPackList"

                    style: TMenuStyle {iconSize:Qt.size(48,48)}
                                 id: style1
                                 objectName: "style1"



                    ExclusiveGroup {

 id: egPack
 objectName: "egPack"

                    }



                    Instantiator {

 id: presetPackInst
 objectName: "presetPackInst"

                        //model: presetController.getPresetPacks(true)

                        MenuItem {
                                    id: MenuItem0
                                    objectName: "MenuItem0"

                            //TODO: find out why this is happenings

                            text: presetPackInst.model[model.index] ? presetPackInst.model[model.index].text : 'All' 

                            checkable: true

                            exclusiveGroup: egPack

                            checked: false

                            onTriggered: {
                                        id: onTriggered1
                                        objectName: "onTriggered1"

                                btPack.packQuery = presetPackInst.model[model.index];

                            }

                        }

                        onObjectAdded: {
                                    id: onObjectAdded0
                                    objectName: "onObjectAdded0"

//                            console.log('jjjjjjjjjjjjjjjjj',object, object.text);

                            presetPackList.insertItem(index, object);

                        }

                    }

                }

            }



            Item {
                        id: Item0
                        objectName: "Item0"

                Layout.preferredWidth: 10

            }



            TToolButtonIcon {
                        id: TToolButtonIcon1
                        objectName: "TToolButtonIcon1"

                Layout.alignment: Qt.AlignRight

                action: Action {
                             id: action1
                             objectName: "action1"

                    text: qsTr("==")

                    iconSource: "qrc:/TControls/icons/center-white.png"

                    onTriggered:  {
                                 id: onTriggered2
                                 objectName: "onTriggered2"

                        presetEdit.popup()

                    }

                }

                Menu {

 id: presetEdit
 objectName: "presetEdit"

                    MenuItem {
                                id: MenuItem1
                                objectName: "MenuItem1"

                        action: actions.actDeletePreset

                        text: "Delete preset"

                    }

                    MenuItem {
                                id: MenuItem2
                                objectName: "MenuItem2"

                        action: actions.actEditPreset

                        text: "Edit preset info..."

                    }

                }

            }

            TToolButtonIcon {
                        id: TToolButtonIcon2
                        objectName: "TToolButtonIcon2"

                Layout.alignment: Qt.AlignRight

                text: qsTr("Edit>")

                iconSource: "qrc:/TControls/icons/center-white.png"

                onClicked: actions.actShowEditing.trigger()

            }



        }

    }

    */



    TDatabase { 

 id: db
 objectName: "db"

    }





    //derp

    Rectangle {
                id: Rectangle1
                objectName: "Rectangle1"

            anchors.top: toolBar.bottom

            anchors.bottom: parent.bottom

            anchors.left: parent.left

            anchors.right: parent.right

            color: "#3F4141"



            TEffectGridView

            {

 id: presetView
 objectName: "presetView"

                        anchors.fill: parent



                        model: 5



                        delegate: Rectangle {
                                     id: delegate0
                                     objectName: "delegate0"



                            width: parent.width

                            height: 20



                        }

            }



    }



    /*Rectangle {



 id: testRectangle
 objectName: "testRectangle"

        height: 100

        width: 100

        color: "red"



    }*/



    Item {

 id: p
 objectName: "p"

    }



}

