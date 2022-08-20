import QtQuick 2.0

Image{
    id: idMuteBtn
//    anchors.verticalCenter: parent.verticalCenter
//    anchors.right: idVolumeBar.left
//    anchors.rightMargin: width/4
//    width: idcontrolArea.height*2/3
    height: width
    property bool condition: true
    property string source1
    property string source2
    source: condition? source1 : source2

    MouseLabel{
        mouseID: idMute
        mouseLabel: parent.mute? qsTr("Unmute") : qsTr("Mute")
        imgID: idMuteBtn
    }

    MouseArea {
        id: idMute
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            myControl.changeMute()
        }
    }

}

