import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 300; height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        objectName: "label"
        text: qsTr("[click to close]")
        anchors.centerIn: parent
        onTextChanged: font.pixelSize = 1

        Behavior on font.pixelSize {
            animation: PropertyAnimation {
                duration: 300
                from: 1
                to: 28
            }
        }
    }
}

