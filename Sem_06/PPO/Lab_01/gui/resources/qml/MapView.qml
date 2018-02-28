import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6
import QtQuick.Controls.Material 2.1
import MyLibrary 1.0

Rectangle {
    id: mapView
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
            line.color: Material.color(Material.Red)
        }
    }

    PositionSource {
        onPositionChanged:  {
            map.center = position.coordinate
        }
    }

    Connections {
        target: mapViewProxy
        onSetPolyline: {
            var lines = []
            for (var i = 0; i < geopath.size(); i++){
                lines[i] = geopath.coordinateAt(i)
            }
            polyline.path = lines
        }
    }
}
