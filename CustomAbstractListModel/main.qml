import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import TunerListModel 1.0
import QtQuick.Layouts 1.1
Window {
    visible: true
    width: 550; height: 200


    // define AbstractListModel implementation (ChannelName, Frequency roles)
    TunerListModel {
        id: tunerModel
    }

    ColumnLayout{
        anchors.fill: parent
        TableView {
            anchors.fill: parent
            model: tunerModel

            TableViewColumn {
                title: "Name"
                role: "Name"
            }

            TableViewColumn {
                title: "Freq"
                role: "Frequency"
            }

            onClicked: {
                console.log(tunerModel.get(row, TunerListModel.Name) + " - " + tunerModel.get(row, TunerListModel.Frequency));
            }
        }

        RowLayout {
            anchors.bottom: parent.bottom
            Button {
                text: "Add First"
                onClicked: tunerModel.addFirst()
            }

            Button {
                text: "Add Last"
                onClicked: tunerModel.addLast()
            }

            Button {
                text: "Update Middle"
                onClicked: tunerModel.updateMiddle()
            }

            Button {
                text: "Remove First"
                onClicked: tunerModel.removeFirst()
            }

            Button {
                text: "Remove Last"
                onClicked: tunerModel.removeLast()
            }
        }
    }
}
