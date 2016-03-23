import QtQuick 2.5
import QtQuick.XmlListModel 2.0
import QtQuick.Layouts 1.1
/**
  Flicker image viewer done in pure QML
  Based on "Qt DevDays 2011, Using Qt Quick for Rapid UI Prototyping and Development: Jens Bache-Wiig"
  https://www.youtube.com/watch?v=k1pnEhyF1pg
 */

// The rectangle is a parent container to all the controls we put on the window
Rectangle {
    id: screen
    width: 400
    height: 550
    color: "#222222"  // pretty dark gray

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
            focus: true

            // A delegate; this guy describes a prototype for a list item
            delegate: Image {
                // item size
                width: parent.width
                height: 100

                // item background
                source: "images/item.png"

                // highlight focused item
                opacity: (focus ? 1 : 0.5)

                // add a smooth fade in/fade out item animation
                Behavior on opacity {
                    NumberAnimation {
                        duration: 600
                        easing.type: Easing.OutQuad
                    }
                }

                // Thumbnail, image title, "show preview" arrow
                RowLayout {
                    anchors.fill: parent

                    // A picture thumbnail the left of the list item
                    Image {
                        id: thumbnail
                        Layout.maximumHeight: parent.height
                        Layout.maximumWidth: parent.height
                        source: imagesource
                    }

                    // Picture title
                    Text {
                        anchors.verticalCenter: parent.verticalCenter

                        // this should be done better, automatically due to RowLayout...
                        Layout.preferredWidth: parent.width - 2 * parent.height

                        elide: Text.ElideRight
                        text: title // flickerModel.title
                        font.pixelSize: 20
                    }

                    // An arrow on the right of the list item
                    Image {
                        id: showPreview
                        source: "images/ShowPreview.png"
                    }
                } // RowLayout

                // Clickable area
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        screen.state = "view"
                        imageView.source = imagesource.replace("_s", "_b") // change medium for big
                    }

                    onEntered: {
                        parent.forceActiveFocus()
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
        source: "images/toolbar.png"
        height: 50
        border.left: 2; border.top: 2
        border.right: 2; border.bottom: 2

        // Search field input
        TextField {
            id: searchField
            anchors.centerIn: parent
            width:200
            text: "Cat"
        }
    }
}
