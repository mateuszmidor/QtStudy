import QtQuick 2.0

// Custom TextField is defined here
// To use it, just input "TextField"
Item {
    property alias text: input.text

    width: 100
    height: 25

    // Background
    BorderImage {
        /*
        border.left: 4
        border.right: 4
        border.top: 4
        border.bottom: 4
        */
        source: "images/edit.png"
        anchors.fill: parent
    }

    // The text input itself
    TextInput {
        id: input
        font.pixelSize: 20
        width: parent.width-16
        anchors.fill: parent
    }
}

