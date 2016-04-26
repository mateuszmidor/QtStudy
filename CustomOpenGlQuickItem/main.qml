import QtQuick 2.3
import QtQuick.Window 2.2

// Import our custom OpenGl module
import OpenGl 1.0


Window {
    visible: true
    width: 640; height: 480

    // our custom OpenGl item, drawn before the entire scene ie. background
    OpenGlItem {
        id: openglCube
        x: 100; y: 100
        width: 300; height: 200

        // make the cube rotate
        NumberAnimation on azimuth {
            duration: 5000
            from: 0
            to: 359
            loops: Animation.Infinite
            running: true
        }

        // make the cube draggable
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis
        }
    }

    Text {
        anchors.top: openglCube.bottom
        anchors.horizontalCenter: openglCube.horizontalCenter
        text: "Drag me!"
        color: "black"
    }
}
