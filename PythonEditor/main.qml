import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: 640
    height: 320
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Python Editor")

    TextEdit {
        anchors.fill: parent
        objectName: "pythonEdit"
        text: "for x in range(0, 3):\n\tprint 'We are on time %d' % (x)"
    }
}

