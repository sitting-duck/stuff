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

            width: parent.width



            ComboBox {

                id: cbCategory
                objectName: "cbCategory"
                Layout.fillWidth: true

                //model: presetController.getCategories(true);



                onCurrentIndexChanged: {

                    //if (presetView) presetView.updatePreset()

                }

                style: PmComboBoxStyle {}



            }



            TToolButtonIcon {

                id: btPack
                objectName: "btPack"
                action: Action {

                    text: qsTr("Pack")

                    iconSource: "qrc:/TControls/icons/center-white.png"

                    onTriggered: {

                        presetPackList.popup()

                    }

                }



                //JSON object

                property var packQuery: ({text:'All'})

                onPackQueryChanged: {

                    // presetView.updatePreset()

                }



                Menu {

                    id: presetPackList
                    objectName: "presetPackList"
                    style: TMenuStyle {iconSize:Qt.size(48,48)}



                    ExclusiveGroup {

                        id: egPack
                        objectName: "egPack"
                    }



                    Instantiator {

                        id: presetPackInst
                        objectName: "presetPackInst"
                        //model: presetController.getPresetPacks(true)

                        MenuItem {

                            //TODO: find out why this is happenings

                            text: presetPackInst.model[model.index] ? presetPackInst.model[model.index].text : 'All' 

                            checkable: true

                            exclusiveGroup: egPack

                            checked: false

                            onTriggered: {

                                btPack.packQuery = presetPackInst.model[model.index];

                            }

                        }

                        onObjectAdded: {

//                            console.log('jjjjjjjjjjjjjjjjj',object, object.text);

                            presetPackList.insertItem(index, object);

                        }

                    }

                }

            }



            Item {

                Layout.preferredWidth: 10

            }



            TToolButtonIcon {

                Layout.alignment: Qt.AlignRight

                action: Action {

                    text: qsTr("==")

                    iconSource: "qrc:/TControls/icons/center-white.png"

                    onTriggered:  {

                        presetEdit.popup()

                    }

                }

                Menu {

                    id: presetEdit
                    objectName: "presetEdit"
                    MenuItem {

                        action: actions.actDeletePreset

                        text: "Delete preset"

                    }

                    MenuItem {

                        action: actions.actEditPreset

                        text: "Edit preset info..."

                    }

                }

            }

            TToolButtonIcon {

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

