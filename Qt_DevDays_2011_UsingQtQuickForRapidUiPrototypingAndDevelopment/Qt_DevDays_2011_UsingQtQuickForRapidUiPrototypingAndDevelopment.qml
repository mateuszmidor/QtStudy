import QtQuick 2.0
import QtQuick.XmlListModel 2.0

/**
  Flicker image viewer done in pure QML
  Based on "Qt DevDays 2011, Using Qt Quick for Rapid UI Prototyping and Development: Jens Bache-Wiig"
  https://www.youtube.com/watch?v=k1pnEhyF1pg
 */
Rectangle {
    id: screen
    width: 360
    height: 500
    color: "yellow"

    // Transitions
    transitions: [
        Transition {
            NumberAnimation {
                target: displayRow
                property: "x"
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }
    ]

    // States
    states: [
        // Image preview
        State {
            name: "view"
            PropertyChanges {
                target: displayRow
                x: -screen.width
            }
        },
        // Image list
        State {
            name: "list"
            PropertyChanges {
                target: displayRow
                x: 0
            }
        }
    ]

    // Flickr XmlListModel
    XmlListModel{
        id: flickerModel
        source: "http://api.flickr.com/services/feeds/photos_public.gne?format=rss2&tags=Cat"
        query: "/rss/channel/item"
        namespaceDeclarations: "declare namespace media=\"http://search.yahoo.com/mrss/\";"
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "imagesource"; query: "media:thumbnail/@url/string()" }
    }

    Row {
        id : displayRow
        width: parent.width
        height: parent.height


        // An item list
        ListView {
            id: listView
            width: parent.width
            height: parent.height

            // Hand made Data model for the ListView
            /*
            ListModel {
                id: listmodel
                ListElement {}
            }
            */
            // Fake the model with fixed 20 items
            model: flickerModel

            // A delegate describes a prototype for a list item
            delegate: Image {
                // item size
                width: parent.width
                height: 80

                // item background
                source: "images/item.jpeg"

                // A picture on the left of the list item
                Image {
                    id: bullet
                    anchors.left: parent.left
                    height: parent.height
                    width: parent.height
                    source: "images/pinguin.jpeg"
                }

                // Some text describing the list item
                Text {
                    anchors.left: bullet.right
                    anchors.verticalCenter: bullet.verticalCenter
                    text: "Item"
                    font.pixelSize: 20
                }

                // A picture on the right of the list item
                Image {
                    source: "images/arrow.jpeg"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    height: parent.height
                    width: parent.height
                }

                // Clickable area
                MouseArea {
                    anchors.fill: parent
                    onClicked: screen.state = "view"
                }
            } // delegate
        } // ListView

        // Image preview
        Image {
            id: imageView
            width: parent.width
            height: parent.height
            source: "images/pinguin.jpeg"

            MouseArea {
                anchors.fill: parent
                onClicked: screen.state = "list"
            }
        }
    }

    // Toolbar
    BorderImage {
        id: toolbar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        source: "images/toolbar.jpeg"
        height: 50
        border.left: 5; border.top: 5
        border.right: 5; border.bottom: 5

        TextField {
            anchors.centerIn: parent
            width:200
        }
    }
}
