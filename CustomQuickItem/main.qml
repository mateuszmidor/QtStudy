import QtQuick 2.3
import QtQuick.Window 2.2

// this is our own created QuickItem being imported
import Shapes 1.0

Window {
    visible: true
    width: 300; height: 200

    Ellipse {
        // set the custom-made property "color"
        color: "orange"

        // set the inherited properties
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 2 / 3; height: parent.height * 2 / 3
    }
}

