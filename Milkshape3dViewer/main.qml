import QtQuick 2.5

import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.0

Item {
    id: panel
    MouseArea {
        anchors.fill: parent
    }

    Rectangle {
        id: rectangle1
        width: 150
        height: 97
        x: 10
        y: 10
        color: "#80d6dff7"
        radius: 13
        border.width: 1
        border.color: "#800b1118"

        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis

            ToolButton {
                id: loadButton
                x: 20
                width: 120
                height: 29
                text: "Load"
                anchors.verticalCenterOffset: -19
                anchors.horizontalCenterOffset: 0
                anchors.top: parent.top
                anchors.topMargin: 15
                opacity: 0.6
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                onClicked: fileDialog.open()
            }

            Slider {
                id: distanceSlider
                x: -28
                y: 57
                width: 120
                antialiasing: true
                tickmarksEnabled: false
                minimumValue: -128
                maximumValue: -4
                value: minimumValue
                anchors.horizontalCenter: parent.horizontalCenter

                onValueChanged: _cameraControl.distance = value
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a model file"
        nameFilters: [ "Milkshape 3D files (*.ms3d)" ]
        onAccepted: {
            _rendererControl.modelFilename = fileDialog.fileUrl.toString().replace("file://", "")
        }
        onRejected: {
        }
    }
}

