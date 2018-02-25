import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6

Rectangle {
    anchors.fill: parent

    Plugin {
        id: osmPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: osmPlugin;

        MapPolyline {
            id: polyline
            line.width: 3
            line.color: 'red'
        }
    }

    PositionSource {
        onPositionChanged:  {
            map.center = position.coordinate
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        property bool mouseDown : false
        property int lastX : -1
        property int lastY : -1
        property var polylinePoints: []

        onPressed : {
            mouseDown = true
            lastX = mouse.x
            lastY = mouse.y
            var coord = map.toCoordinate(Qt.point(lastX, lastY))

            if (mouse.button & Qt.LeftButton) {
                polylinePoints.push(coord)
                polyline.addCoordinate(coord)
            } else {
                polyline.removeCoordinate(polylinePoints.pop())
            }
        }

        onReleased : {
            mouseDown = false
            lastX = -1
            lastY = -1
        }

        onPositionChanged: {
            if (mouseDown) {
                var dx = mouse.x - lastX
                var dy = mouse.y - lastY
                map.pan(-dx, -dy)
                lastX = mouse.x
                lastY = mouse.y
            }
        }
    }
}
