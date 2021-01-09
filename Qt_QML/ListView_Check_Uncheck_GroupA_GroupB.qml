ListView { // ListView if one of group a is checked, uncheck all of group b. If one of group b is checked, uncheck all of group a. Pulls models from backend object.
            id: listView
            width: 400
            height: 250
            property var checklist: [false, true, false]
            model: backend ? backend.getItems() : 0
            spacing: 3
            delegate: Item {
                property var isChecked: checkbox.checked
                width: inputBox.width + checkbox.width + 100
                height: 30
                RowLayout {
                    id: rl
                    anchors.fill: parent
                    //
                    CheckBox {
                        id: checkbox
                        Layout.leftMargin: 8
                        enabled: !listView.model[index].includes("Never")
                        text: ""
                        ToolTip.delay: Style.toolTipDelay; ToolTip.timeout: Style.toolTipTimeout
                        ToolTip.text: qsTr("Enable device")
                        ToolTip.visible: hovered
                        checked: listView.checklist[index]
                        onClicked: {
                            //console.log("checked: ", checked)
                            listView.checklist[index] = (checkState === Qt.Checked)
                            update(backend.getItems(), listView.checklist, (checkState === Qt.Checked));
                        }
                        function update(devices, checklist, checked) {

                            var gpuChecked = isAChecked(backend.getItems(), listView.checklist);
                            var cpuChecked = isBChecked(backend.getItems(), listView.checklist);
                            console.log("cpuChecked: ", cpuChecked)
                            console.log("gpuChecked: ", gpuChecked)
                            console.log("checked: ", checked)
                            if(checked && index===0) {
                                setCPU(true, backend.getItems(), listView.checklist);
                                setGPU(!cpuChecked, backend.getItems(), listView.checklist);
                            }
                            if(checked && index!==0) {
                                setCPU(false, backend.getItems(), listView.checklist);
                                setGPU(true, backend.getItems(), listView.checklist);
                            }


                        }
                        function setCPU(value, devices, checklist) {
                            for(var d in devices) {
                                if(devices[d].includes("A")) {
                                    checklist[d] = value;
                                    listView.checklist = checklist;
                                    return;
                                }
                            }
                        }
                        function setGPU(value, devices, checklist) {
                            for(var d in devices) {
                                if(devices[d].includes("B") || devices[d].includes("Bb")) {
                                    checklist[d] = value;
                                    listView.checklist = checklist;
                                    return;
                                }
                            }
                        }
                        function isAChecked(devices, checklist) {
                            for(var d in devices) {
                                if(devices[d].includes("B") || d.includes("Bb")) {
                                    if(checklist[d]) {
                                        return true;
                                    }
                                }
                            }
                            return false;
                        }
                        function isBChecked(devices, checklist) {
                            for(var d in devices) {
                                if(devices[d].includes("A")) {
                                    if(checklist[d]) {
                                        return true;
                                    }
                                }
                            }
                            return false;
                        }

                        function isChecked(name) {
                            if(name.includes("Never")) {
                                return false;
                            } else if(name.includes("A") && !machineHasGPU(backend.getItems())) {
                                return true;
                            } else if(name.includes("A") && machineHasGPU(backend.getItems())) {
                                return false;
                            } else if(name.includes("B") || name.includes("Bb")) {
                                return true;
                            }
                        }
                    }
                    Item {
                        width: inputBox.width + checkbox.width + 80
                        height: 30
                        Layout.fillWidth: true
                        InputBox {
                            id: inputBox
                            anchors.left: parent.left
                            inputVisible: !listView.model[index].includes("A")
                            label: listView.model[index]
                            enabled: listView.model[index].includes("Never") ? false : checkbox.checked
                            suffix: ""
                            toolTip: "Adjust for each"
                            labelWidth: 2.6
                            value: listView.model[index].includes("Never") ? 0 : 2
                            minValue: 1
                            maxValue: 5
                            onValueUpdated: {
                                console.log("do a thing");
                            }
                        }
                    }

                }
            }
        }
