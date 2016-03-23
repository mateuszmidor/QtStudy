import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

Rectangle {
    id: window
    width: 150
    height: 450
    visible: true

    // Define states for the traffic light
    states: [
        // STOP light
        State {
            name: "stop"
            PropertyChanges {
                target: redLight
                color: "red"
            }
            PropertyChanges {
                target: greenLight
                color: "#002200"
            }
        },

        // GO light
        State {
            name: "go"
            PropertyChanges {
                target: redLight
                color: "#220000"
            }
            PropertyChanges {
                target: greenLight
                color: "green"
            }
        }
    ]

    // Define animation for states transitions
    transitions: [
        Transition {
                from: "stop"
                to: "go"
                PropertyAnimation {
                    target: redLight
                    property: "color"
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
            },
        Transition {
                from: "go"
                to: "stop"
                PropertyAnimation {
                    target: greenLight
                    property: "color"
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
            }
    ]

    // Initial state
    state: "stop"

    // Light post representation
    Rectangle {
        id: lightCase
        x: 14
        y: 13
        width: 120
        height: 242
        color: "black"
        radius: 49
        border.color: "gray"

        Rectangle {
            id: redLight
            x: 24
            y: 33
            width: 82
            height: 76
            color: "red"
            radius: 38
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            id: greenLight
            x: 17
            y: 130
            width: 82
            height: 76
            color: "green"
            radius: 38
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 0
        }
    }

    Button {
        id: button1
        x: 44
        y: 415
        text: qsTr("switch!")
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: parent.state = (parent.state == "go" ? "stop" : "go")
    }

    Rectangle {
        id: rectangle1
        x: 55
        y: 252
        width: 20
        height: 157
        color: "#000000"
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

