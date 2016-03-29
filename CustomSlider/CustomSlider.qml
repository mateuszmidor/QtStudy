import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 640; height: 320

    // slider
    Rectangle {
        id: slider
        width: parent.width * 2 / 3; height: 40
        color: "lightblue"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 10
        signal scroll(real value)

        // slider handle
        Rectangle {
            id: handle
            width: parent.height; height: parent.height
            color: "red"
            radius: 10

            // emit onScroll event
            onXChanged: slider.scroll(handle.x  / (slider.width - handle.width))

            MouseArea {
                anchors.fill: parent
                drag.target: parent
                drag.axis: "XAxis"
                drag.minimumX: 0
                drag.maximumX: slider.width - handle.width
            }
        }

        // handle onScroll event
        onScroll: window.title = Math.round(value * 100)
    }



}

