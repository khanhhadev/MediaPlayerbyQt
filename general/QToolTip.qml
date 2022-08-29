import QtQuick 2.0
import "../libs/Lib.js" as RS

Text {
    id: playtext
    property MouseArea mouseID
    property string btnLabel

    property Item btnID

    font.pixelSize: 16
    text: mouseID.containsMouse? btnLabel : ""
    color: parent.focus? RS.Color.songtext1 : RS.Color.songtext2
    z: 2

    Rectangle {
        id: textFrame
        implicitHeight: parent.height
        implicitWidth: parent.width
        radius: 3
        z: -1
        opacity: 0.9
        scale: mouseID.containsMouse? 1.2 : 1
        color: mouseID.containsMouse? "white": "transparent"
    }

    states: [State{
            when: mouseID.containsMouse

            PropertyChanges {
                target: playtext
                x: mouseID.mouseX
                y: mouseID.mouseY
            }
            PropertyChanges {
                target: btnID
                scale: 1.2
            }
        }]
}
