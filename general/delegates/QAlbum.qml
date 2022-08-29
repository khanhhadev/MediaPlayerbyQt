import QtQuick 2.0
import CustomImage 1.0
import "../../libs/Lib.js" as RS


Rectangle{
    //        id: idRect
    id: albumDelegate
    signal clicked()
    signal doubleClicked()
    property bool hoverEnabled: true
    width: 100
    height: 140
    color: focus? RS.Color.songback1 : RS.Color.songback2
    border.color: (focus||boxArea.containsMouse)? RS.Color.songborder1 : "transparent"/*RS.Color.songborder2*/
    scale: boxArea.containsMouse? 1.1 : 1

    ImageItem{
        y: 10
        image: eimage
        width: 100
        height: width

        MouseArea {
            id: boxArea
            anchors.fill: parent
            hoverEnabled: albumDelegate.hoverEnabled
            onClicked: {
                albumDelegate.clicked()
            }
            onDoubleClicked: {
                albumDelegate.doubleClicked()
            }
        }
    }
    Text {
        id: idTextBox
        text: album
        fontSizeMode: Text.Fit
        color: parent.focus? RS.Color.songtext1 : RS.Color.songtext2
        //        elide: Text.ElideRight
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        anchors.fill: parent
    }
}
