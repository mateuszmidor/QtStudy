import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import Plugin 0.1 // our CustomPlugin, loaded from Plugin/libPlugin.so

Item {
    id: screen

    ListView {
        id: listview
        height: screen.height*0.9
        width:screen.width
        model: Tuner.channelList // Tuner is a singleton; accessed by type name not by id
        highlight: highlight
        highlightFollowsCurrentItem: true
        focus: true

        delegate: Rectangle {
            id: background
            width: parent.width
            height: 80
            opacity: (focus ? 1 : 0.5)

            // add a smooth fade in/fade out item animation
            Behavior on opacity {
                NumberAnimation {
                    duration: 600
                    easing.type: Easing.OutQuad
                }
            }
                
            Column {
                Row {
                    Text {
                        font.pixelSize: 20
                        text: StationNum + "."
                    }
                    Text {
                        text: "\"" + StationName + "\""
                        font.pixelSize: 20
                    }
                }

                Row {
                    Text {
                        font.pixelSize: 20
                        text: "Artist: " + Artist
                    }
                    Text {
                        font.pixelSize: 20
                        text: "  Title: \"" + Title + "\""
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                
                // tune to serviceid
                onClicked: Tuner.currentChannelId = StationNum;
                
                // set focus on item
                onEntered: parent.forceActiveFocus()
            }
        }
    }
}
