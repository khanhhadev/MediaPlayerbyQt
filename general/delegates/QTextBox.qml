import QtQuick 2.0
import "../../libs/Lib.js" as RS

Rectangle{
    id: idRect
    property bool textRunning: idRect.focus
    property string text
    signal clicked()
    signal doubleClicked()
    property bool hoverEnabled: true
    height: 50
    radius: 3
    opacity: 1
    clip: true
    color: focus? RS.Color.songback1 : RS.Color.songback2
    border.color: focus? RS.Color.songborder1 : RS.Color.songborder2
    scale: boxArea.containsMouse? 1.1 : 1

    Text {
        id: idTextBox
        text: parent.text
        fontSizeMode: Text.Fit
        color: parent.focus? RS.Color.songtext1 : RS.Color.songtext2
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
    }

    //text moving animation
    NumberAnimation{
        properties: "x"
        target: idTextBox
        from: idRect.x
        to: idRect.x - idRect.width
        duration: 4000
        loops: Animation.Infinite
        running: textRunning
    }

    MouseArea {
        id: boxArea
        anchors.fill: parent
        hoverEnabled: idRect.hoverEnabled
        onClicked: {
            parent.clicked()
        }
        onDoubleClicked: {
            parent.doubleClicked()
        }
    }

    onFocusChanged: {
        if (!focus) idTextBox.x = parent.x
    }

//    states: [
//        State {
//            when:
//            PropertyChanges {
//                target: idRect
//                scale: 1.1
//            }
//        }
//    ]
}
