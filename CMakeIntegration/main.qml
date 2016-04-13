import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 300
    height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("CMake Hello World")
        font.bold: true
        font.pointSize: 18
        style: Text.Normal
        anchors.centerIn: parent
    }
}

