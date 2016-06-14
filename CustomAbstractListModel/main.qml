import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import TunerListModel 1.0

Window {
    visible: true
    width: 350; height: 200


    // define AbstractListModel implementation (ChannelName, Frequency roles)
    TunerListModel {
        id: tunerModel
    }

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
            console.log(tunerModel.get(row, 0) + " - " + tunerModel.get(row, 1));
        }
    }
}

