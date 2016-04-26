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
        height: 40
        color: "#80d6dff7"
        radius: 13
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        border.width: 1
        border.color: "#800b1118"

        ToolButton {
            id: loadButton
            x: 49
            y: 21
            width: 120
            height: 29
            text: "Load"
            opacity: 0.6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            onClicked: fileDialog.open()
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

