import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import Plugin 0.1 // our CustomPlugin, loaded from Plugin/libPlugin.so

Window {
    visible: true
    width: 350; height: 750
    x: (Screen.desktopAvailableWidth - width) / 2
    y: (Screen.desktopAvailableHeight - height) / 2


    ColumnLayout {
        anchors.fill: parent

		ChannelListView {
        	id: channellist
        	anchors.fill: parent
        	anchors.leftMargin: 30
        	anchors.topMargin: 30
        	anchors.rightMargin: 30
        	anchors.bottomMargin: 30        	
        }


        // current channel radiotext
        Text {
            id: radiotext
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                bottomMargin: 30
            }
            horizontalAlignment: TextInput.AlignHCenter
            text: Tuner.contentDescription // Tuner is a singleton; accessed by type name not by id
            font.pixelSize: 40
            font.bold: true
        }
    }
}