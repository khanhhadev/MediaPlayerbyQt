import QtQuick 2.0
import "../libs/Lib.js" as RS


Rectangle{
    id: idRect
    property bool hovered: boxArea.containsMouse
    property string text
    signal clicked()
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("main window created")
    }

    height: 20
    width: 80
    opacity: 1
    clip: true
    color: boxArea.containsMouse?RS.Color.songback1 : RS.Color.songback2

    Text {
        id: idTextBox
        text: parent.text
        fontSizeMode: Text.Fit
        color: boxArea.containsMouse? RS.Color.songtext1 : RS.Color.songtext2
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
    }

    MouseArea {
        id: boxArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            idRect.clicked()
        }
    }
}
