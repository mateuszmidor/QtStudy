import QtQuick 2.3
import QtQuick.Window 2.2

// this is our own created QuickItem being imported
import Shapes 1.0

Window {
    visible: true
    width: 400; height: 200

    // create chart background
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 2 / 3; height: parent.height * 2 / 3
        color: "lightgray"
        border.color: "darkgray"

        // add custom made BarChart
        BarChart {
            // set custom property
            style: BarChart.Fill

            // set the inherited properties
            anchors.fill: parent
            anchors.leftMargin: 3; anchors.rightMargin: 3

            // add a list of bars to the chart
            bars: [
                Bar { value: 0.3 },
                Bar { value: 0.9 },
                Bar { value: 0.7 },
                Bar { value: 0.4 },
                Bar { value: 0.2 },
                Bar { value: 0.5 }
            ]

            // handle mouse
            MouseArea {
                anchors.fill: parent
                onClicked: parent.toggleFillStyle() // call item slot function
            }
        } // BarChart
    } // Rectangle

} // Window

