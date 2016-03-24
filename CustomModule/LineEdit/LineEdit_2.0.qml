import QtQuick 2.0

// Rounded, skew LineEdit
Item {
    width: 200
    height: 20
    rotation: 5

    Rectangle {
        anchors.fill: parent
        color: "#d2b4ea"
        radius: 5
        border.width: 2
        border.color: "#600404"

        TextInput {
            anchors.fill: parent
            text: "Edit v 2.0..."
            anchors.rightMargin: 5
            anchors.leftMargin: 5
        }
        clip: true
    }
}
