import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

// a window for displaying contents
Window {
    visible: true
    width: 300; height: 200

    // background image
    Image {
        anchors.fill: parent
        source: "images/toolbar.png"
    }

    // arrange elements in rows
    RowLayout {
        anchors.fill: parent

        // SiriusXM label
        Text {
            text: "SiriusXM"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top : parent.top
            anchors.topMargin: 10
            font.pixelSize: parent.height / 12
            color: "gray"
        }

        // channel name
        Text {
            // here we load channel name from qobject
            text: qobject.channelName;

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: parent.height / 6
            font.bold: true
            color: "white"
        }

        // tune button
        Button {
            // here we forward button clicked event to qobject
            onClicked: qobject.nextChannelClicked()

            id: button1
            text: qsTr("Tune!")

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10          
        }
    }
}
