import QtQuick 2.5

import QtQuick.Window 2.2


Item {
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        color: "Yellow"
        anchors.centerIn: parent
    }
}

