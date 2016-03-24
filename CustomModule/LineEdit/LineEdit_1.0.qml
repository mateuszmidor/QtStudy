import QtQuick 2.0

// Rectangular LineEdit
Item {
    id: lineEdit
    width: 200
    height: 20

    Rectangle {
        anchors.fill: parent
        color: "#b5eae7"
        border.width: 2
        border.color: "#600404"

        TextInput {
            anchors.fill: parent
            text: "Edit v 1.0..."
            anchors.rightMargin: 5
            anchors.leftMargin: 5
        }
        clip: true
    }
}
