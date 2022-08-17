import QtQuick 2.0

Text {
    id: playtext
    property MouseArea mouseID
    property string mouseLabel

    property Rectangle rectID
    property Image imgID

    font.pixelSize: 16
    text: ""
    z: parent.z + 2

    Rectangle {
        id: textFrame
        implicitHeight: parent.height
        implicitWidth: parent.width
        radius: 3
        z: -1
        opacity: 0.9
        color: "white"
    }

    states: [State{
            when: mouseID.containsMouse

            PropertyChanges {
                target: playtext
                x: mouseID.mouseX
                y: mouseID.mouseY
                text: mouseLabel
            }

            PropertyChanges {
                target: textFrame
                color: "white"
            }

            PropertyChanges {
                target: imgID
                scale: 1.2
            }
        }]
}
