import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("BoostPythonIntegration demo")

   ColumnLayout {

        spacing: 5
        anchors.fill: parent
        TextArea {
            id: pythonEditor
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "print 'Hello from python!'"
        }
        Button {
            text: "run!"
            anchors.horizontalCenter: parent.horizontalCenter
            transformOrigin: Item.Center
            onClicked: _python.run(pythonEditor.text)
        }
        TextArea {
            id: pythonOutput
            Layout.fillWidth: true
            text: _python.output
            textColor: "#12550a"
            font.family: "FreeMono"
            readOnly: true
        }
    }
}

