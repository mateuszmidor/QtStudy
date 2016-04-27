import QtQuick 2.0

Item {
    property int lastX
    property int lastY
    signal dragLeft(int dx, int dy)
    signal dragRight(int dx, int dy)

    MouseArea {
        anchors.fill: parent
        onPressed: { lastX = mouseX; lastY = mouseY; }
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPositionChanged: {
            if (mouse.buttons & Qt.LeftButton)
                parent.dragLeft(mouseX - lastX, mouseY - lastY);
            else
            if (mouse.buttons & Qt.RightButton)
                parent.dragRight(mouseX - lastX, mouseY - lastY);

            lastX = mouseX; lastY = mouseY;
        }
    }
}

