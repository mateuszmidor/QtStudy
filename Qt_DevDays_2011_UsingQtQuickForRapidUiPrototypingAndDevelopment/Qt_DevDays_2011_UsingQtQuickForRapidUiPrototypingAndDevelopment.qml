import QtQuick 2.0
import QtQuick.XmlListModel 2.0

/**
  Flicker image viewer done in pure QML
  Based on "Qt DevDays 2011, Using Qt Quick for Rapid UI Prototyping and Development: Jens Bache-Wiig"
  https://www.youtube.com/watch?v=k1pnEhyF1pg
 */

// The rectangle is a parent container to all the controls we put on the window
Rectangle {
    id: screen
    width: 360
    height: 500
    color: "yellow"

    // Transitions(animations)
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

    // States(image list view/selected image preview)
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

    // Flickr XmlListModel; for fetching items from flickr
    XmlListModel{
        id: flickerModel
        source: "http://api.flickr.com/services/feeds/photos_public.gne?format=rss2&tags=" + searchField.text
        query: "/rss/channel/item"
        namespaceDeclarations: "declare namespace media=\"http://search.yahoo.com/mrss/\";"
        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "imagesource"; query: "media:thumbnail/@url/string()" }
    }

    // This row layout contains our image list and image preview
    Row {
        id : displayRow
        width: parent.width
        height: parent.height


        // An image list
        ListView {
            id: listView
            width: parent.width
            height: parent.height

            // Assign the flickerModel; to populate the list view with images from flickr
            model: flickerModel

            // A delegate; this guy describes a prototype for a list item
            delegate: Image {
                // item size
                width: parent.width
                height: 80

                // item background
                source: "images/item.jpeg"

                // A picture thumbnail the left of the list item
                Image {
                    id: thumbnail
                    anchors.left: parent.left
                    height: parent.height
                    width: parent.height
                    source: imagesource
                }

                // Picture title
                Text {
                    anchors.left: thumbnail.right
                    anchors.verticalCenter: thumbnail.verticalCenter
                    text: title // flickerModel.title
                    font.pixelSize: 20
                }

                // An arrow on the right of the list item
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
                    onClicked: {
                        screen.state = "view"
                        imageView.source = imagesource.replace("_m", "_b") // change medium for big
                    }
                }
            } // delegate
        } // ListView

        // Image preview
        Image {
            id: imageView
            width: parent.width
            height: parent.height
            source: "images/pinguin.jpeg"
            fillMode: Image.PreserveAspectFit

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

        // Search field input
        TextField {
            id: searchField
            anchors.centerIn: parent
            width:200
            text: "Cat"
        }
    }
}
