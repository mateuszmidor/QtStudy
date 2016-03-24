import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 150
    height: 200

    // Just list of colors
    ListModel {
        id: colorsModel
        ListElement { name: "red" }
        ListElement { name: "green" }
        ListElement { name: "blue" }
        ListElement { name: "orange" }
        ListElement { name: "navy" }
    }

    // ListView delegate (draws item representation) - must be a Component
    Component {
        id: colorsDelegate

        Item {
            id: colorsDelegateItem
            width: parent.width
            height: 30

            // 1. If this is the current item, then make it bigger
            states: State {
                name: "current"
                when: (advancedListView.currentIndex == index)
                PropertyChanges  { target: colorsDelegateItem; height: 40 }
            }

            // 2. Make the item growing animated
            Behavior on height {
                NumberAnimation {
                    duration: 250
                    easing.type: Easing.OutQuad
                }
            }

            // 3. Draw item name
            Text {
                text: name
                color: name
                font.pixelSize: parent.height - 4
                anchors.verticalCenter: parent.verticalCenter
            }

            // 4. Clicking an item needs manual handling - provide it
            MouseArea {
                anchors.fill: parent
                onClicked: advancedListView.currentIndex = index
            }
        }
    }

    // Our advanced list view
    ListView {
        id: advancedListView
        anchors.fill: parent
        focus: true
        clip: true
        model: colorsModel
        delegate: colorsDelegate

        // Draw this before first item
        header: Rectangle {
            width: parent.width; height: 10; color: "lightgreen"
        }

        // Draw this after last item
        footer: Rectangle {
            width: parent.width; height: 10; color: "lightblue"
        }

        // Draw this as a background of the currently selected item
        highlight: Rectangle {
            width: parent.width; height: 10; color: "lightgray"
        }
    }
}
