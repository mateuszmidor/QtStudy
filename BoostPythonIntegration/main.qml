import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("BoostPythonIntegration demo")

   Column {

        spacing: 5
        anchors.fill: parent
        TextArea {
            id: pythonEditor
            tabChangesFocus: false
            width: parent.width
            text: "print 'Hello from python!'"
        }
        Button {
            text: "run!"
            anchors.horizontalCenter: parent.horizontalCenter
            transformOrigin: Item.Center
            onClicked: _python.run(pythonEditor.text)
        }
        TextArea {
            width: parent.width
            text: _python.output
            readOnly: true
        }
    }
}

