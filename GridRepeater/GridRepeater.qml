import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 400
    height: 400

    Rectangle {
        anchors.fill: parent
        color: "black"

        Grid {
            x: 5
            y: 5
            rows: 5
            columns: 5
            spacing: 10

            Repeater {
                model: 25 // repeat 25 times

                // Rectangle to be repeated. Position automatically inside the Grid cells
                Rectangle {
                    width: 70; height: 70


                    color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0) // random color
                    // color: (index % 2 == 0) ? "white" : "brown" // chessboard pattern for odd column number board

                    // Embed an index label
                    Text {
                        text: index // index is provided by the Repeater
                        anchors.centerIn: parent
                        font.pixelSize: 24
                    }
                }
            }
        }
    }
}

