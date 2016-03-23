import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0


// Declare the application main window
ApplicationWindow {

    // 1. Setup the basic window params
    id: root        // id allows components to be referenced to
    visible: true   // start with visible window
    width: 500      // starting width
    height: 300     // starting height
    title: "MainWnd"
    minimumWidth: mainToolbar.implicitWidth // minimum width the mainToolbar allows to be shrinked to


    // 2. Add a toolbar with buttons at the top of the window
    toolBar: ToolBar {
        id: mainToolbar

        RowLayout {
            width: parent.width // ensure the toolbar uses the entire width of the window

            // Add yellow button
            ToolButton {
                text: "make yellow"
                // iconSource:  // an icon can be assigned to the button
                onClicked: root.color = "yellow"
            }

            // Add lime button
            ToolButton {
                text: "make lime"
                // iconSource:
                onClicked: root.color = "lime"
            }

            // Add a slider
            Slider {
                id: slider
                Layout.fillWidth: true
                implicitWidth: 50 // minimum width the slider can be shrinked to
                onValueChanged: root.title = value
                minimumValue: 0
                maximumValue: 100
                stepSize: 1
            }

            // Add a text field
            TextField {
                text: "title..."
                onTextChanged: root.title = text
            }
        }
    }

    // 3. Add the window contents arranged in a side-by-side layout
    RowLayout {

        // 2.1 Add an exit button
        Button {
            text: "EXIT"
            onClicked: root.close() // close the main window
        }

        // 2.2 Create exclusive radiobutton group...
        ExclusiveGroup {
            id: exclusiveButtons
        }

        // 2.3 ...and add a sample groupbox with radio buttons
        GroupBox {
            title: "GroupBox"
            ColumnLayout {
                RadioButton { text: "radio1"; exclusiveGroup: exclusiveButtons }
                RadioButton { text: "radio2"; exclusiveGroup: exclusiveButtons }
                RadioButton { text: "radio3"; exclusiveGroup: exclusiveButtons }
            }
        }

        // 2.4 Add a simple table View
        TableView {
            TableViewColumn { title: "Column1" }
            model: 6 // fake the model to present 6 empty rows
        }
    }

    // 4. Add a status bar
    statusBar: StatusBar {
        RowLayout {
            width: parent.width

            Label {
                text: "status: "
            }

            Label {
                text: root.title
            }

            ProgressBar {
                anchors.right: parent.right
                minimumValue: slider.minimumValue
                maximumValue: slider.maximumValue
                value: slider.value
            }
        }
    }
}
