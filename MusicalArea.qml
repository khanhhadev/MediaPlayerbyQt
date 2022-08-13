import QtQuick 2.0
import Qt.labs.platform
import "ImageLib.js" as Pic


Rectangle{
    radius: 5
    opacity: 0.6
    color: "white"
    z: -1
    width: 2*parent.width/3
    height: 2*parent.height/3

    Rectangle {
        anchors.centerIn: parent;
        width: parent.width/3
        height: width
        radius: width/2
        clip: true

        Image {
            id: idMusicPlay
            width: parent.width
            height: width
//            anchors.fill: parent
            anchors.centerIn: parent;
            opacity: 0.8
            source: Pic.main
        }

        RotationAnimation{
            target: idMusicPlay
            loops: Animation.Infinite
            from: 0
            to: -360
            duration: 15000;
            direction: RotationAnimation.Counterclockwise
            running: (myPlayer.state === 1)? true: false
        }

        RotationAnimation{
            id: coverArtreturn
            target: idMusicPlay
            to: 0
            direction: RotationAnimation.Counterclockwise
            running: (myPlayer.state === 0)? true: false
        }
    }

}
