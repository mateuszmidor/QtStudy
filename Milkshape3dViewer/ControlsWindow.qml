import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.0

// controls window
Rectangle {
    id: controlsWindow
    width: 150
    height: 60
    x: 10
    y: 10
    color: "#80d6dff7"
    radius: 13
    border.width: 1
    border.color: "#800b1118"
    clip: true

    property alias distanceSlider: distanceSlider
    signal modelFileSelected(string filename)
    signal distanceChanged(int distance)

    // smoothly rollout the window down
    Behavior on height {
        SequentialAnimation {
            PauseAnimation {
                duration: 500
            }
            NumberAnimation {
                duration: 600
                easing.type: Easing.InOutQuad
            }
        }
    }

    // allow for dragging around the window
    MouseArea {
        anchors.fill: parent
        drag.target: parent
        drag.axis: Drag.XAndYAxis

        // model load button
        Button {
            id: loadButton
            y: 15
            width: 120
            height: 30
            text: "Load"
            opacity: 0.6
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: fileDialog.open()
        }

        // distance control
        Slider {
            id: distanceSlider
            y: 60
            width: 120
            antialiasing: true
            tickmarksEnabled: false
            minimumValue: -256
            maximumValue: -4
            value: minimumValue
            anchors.horizontalCenter: parent.horizontalCenter
            onValueChanged: distanceChanged(value)
        }
    }

    // loading mode from file
    FileDialog {
        id: fileDialog
        title: "Please choose a model file"
        nameFilters: [ "Milkshape 3D files (*.ms3d)" ]
        onAccepted: {
            modelFileSelected(fileDialog.fileUrl.toString().replace("file://", ""))
            controlsWindow.height = 100
        }
    }
}
