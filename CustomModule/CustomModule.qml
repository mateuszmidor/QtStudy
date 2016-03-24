import QtQuick 2.5
import QtQuick.Window 2.2

/*
  To make a custom component:
  -create subdirectory with the component name. Here: "LineEdit"
  -create qmldir file inside, that describes available versions of the component, eg. "LineEdit 1.0 LineEdit_1.0.qml"
  -add component implementation qml files, eg. "LineEdit_1.0.qml"
*/


// To make the below import possible, add current directory in .qmlproject file: 'importPaths: [ "." ]'
// Mind also, there is "qmldir" file inside "LineEdit" directory, that is not shown in the project tree view
import LineEdit 2.0 as LE2 // import into namespace to access both versions. Now the namespace LE2 is reqired to access LineEdit component
import LineEdit 1.0 as LE1

Window {
    visible: true
    width: 300
    height: 100


    // The below can be marked "Unknown component. (M300)", but it still works during runtime
    LE1.LineEdit {
        y: 20
        anchors.horizontalCenter: parent.horizontalCenter
    }

    LE2.LineEdit {
        y: 60
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
