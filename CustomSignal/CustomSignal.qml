import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: window
    width: 100
    height: 100
    visible: true

    // Define a checkbox
    Rectangle {
        id: myCheckBox
        width: parent.width
        height: 30
        radius: 7
        border.width: 3
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter


        // Here comes the actual checkbox features
        property bool isChecked: true

        // Define own signal that can be emitted from the checkbox
        signal toggle()

        // Define the slot. It is automatically tied to the signal  based on the signal name: signal = onSignal
        onToggle: isChecked = !isChecked

        // Handle check/uncheck
        MouseArea {
            anchors.fill: parent
            onClicked: parent.toggle()
        }

        // Present isChecked value
        Text {
            id: label
            text: parent.isChecked ? "Checked" : "Not checked"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
