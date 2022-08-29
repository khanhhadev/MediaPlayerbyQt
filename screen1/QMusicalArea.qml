import QtQuick 2.0
import CustomImage 1.0
import "../libs/Lib.js" as RS
import "../general"


Rectangle{
    property QtObject currentImage
    opacity: 0.6
    color: "transparent"
    z: -1
    Rectangle {
        anchors.centerIn: parent;
        width: parent.width/3
        height: width
        radius: width/2
        clip: true

        ImageItem {
            image: myPlayer.image
            id: idMusicPlay
            width: parent.width
            height: width
            anchors.centerIn: parent;
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
