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
            line.color: 'green'
        }
    }

    PositionSource {
        onPositionChanged:  {
            map.center = position.coordinate
        }
    }

    MouseArea {
        anchors.fill: parent
        property bool mouseDown : false
        property int lastX : -1
        property int lastY : -1

        onPressed : {
            mouseDown = true
            lastX = mouse.x
            lastY = mouse.y
            polyline.addCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)))
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
