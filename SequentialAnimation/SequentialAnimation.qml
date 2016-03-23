import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: window1
    width: 200
    height: 200
    visible: true

    Rectangle {
        id: circle
        x: 0
        y: 0
        width: 200
        height: 200
        color: "#d01414"
        radius: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        SequentialAnimation {
            // grow
            NumberAnimation {
                target: circle
                properties: "width, height"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 0; to: 200
            }

            // shrink
            NumberAnimation {
                target: circle
                properties: "width, height"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 200; to: 0
            }

            // wait
            PauseAnimation {
                duration: 1000
            }

            running: true // start running immediately
            loops: Animation.Infinite // run forever
        }
    }
}
