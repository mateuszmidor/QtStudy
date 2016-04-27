import QtQuick 2.5
import QtQuick.Window 2.2

// qml context variables: _cameraControl, _rendererControl

Item {
    // capture mouse drag and use it for model zoom/rotate
    DragArea {
        anchors.fill: parent
        onDragLeft: {_cameraControl.azimuth += dx; _cameraControl.elevation += dy; }
        onDragRight: controlsWindow.distanceSlider.value += dy;

        // window with all necessary controls for model viewing
        ControlsWindow {
            id: controlsWindow
            onModelFileSelected: _rendererControl.modelFilename = filename
            onDistanceChanged: _cameraControl.distance = distance
        }
    }
}
