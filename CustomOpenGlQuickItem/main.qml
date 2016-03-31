import QtQuick 2.3
import QtQuick.Window 2.2

// Import our custom OpenGl module
import OpenGl 1.0


Window {
    visible: true
    width: 640; height: 480

    // our custom OpenGl item, drawn before the entire scene ie. background
    OpenGlItem {
        anchors.fill: parent
    }

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Regular QML control over OpenGl drawn background"
        color: "white"
    }
}

