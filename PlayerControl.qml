import QtQuick 2.0
import QtMultimedia
import "ImageLib.js" as Pic

Item {

    //current playing time
    Text{
        id: songPosition
        anchors.verticalCenter: idProgressBar.verticalCenter
        anchors.left: parent.left
        text: myPlayer.positionText
    }

    //total time of song
    Text{
        id: songDuration
        anchors.verticalCenter: idProgressBar.verticalCenter
        anchors.right: parent.right
        text: myPlayer.durationText
    }

    //song progress display
    MSlider{
        id: idProgressBar
        anchors.top: parent.top
        anchors.left: songPosition.right
        anchors.right: songDuration.left
        anchors.margins: 10
        radius: 3
        height: 12
        clip: true
        color: "white"
        maxValue: myPlayer.duration
        currentValue: myPlayer.position
        onMcurrentValueChanged: (value)=> {
                                    myPlayer.position = value

                                }
    }

    //volume display
    MSlider{
        id: idVolumeBar
        anchors.left: idMuteBtn.right
        anchors.right: songDuration.right
        anchors.margins: 3
        anchors.verticalCenter: parent.verticalCenter
        radius: 3
        height: 7
        mheight: height*1.2
        color: "white"
        clip: true
        maxValue: 1
        currentValue: myPlayer.volume
        onMcurrentValueChanged: (value)=> {
                                    myPlayer.volume = value
                                }
    }

    //mute/unmute button
    Image{
        id: idMuteBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: idcontrolArea.right
        anchors.leftMargin: idcontrolArea.height/2
        width: idcontrolArea.height/2
        height: width
        property bool mute: (myPlayer.volume === 0)||(myPlayer.muted)
        source: mute? Pic.mute : Pic.volume
        MouseArea {
            id: idMute
            anchors.fill: parent
            onClicked: {
                myControl.changeMute()
            }
        }

    }

    Image{
        id: idRepeatBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: idcontrolArea.left
        anchors.rightMargin: idcontrolArea.height/2
        width: 2*idcontrolArea.height/3
        height: width
        source: Pic.repeat
        MouseArea {
            id: idRepeat
            anchors.fill: parent
            onClicked: {
                myControl.changeRepeat()
            }
        }
        Rectangle{
            implicitHeight: parent.height
            implicitWidth: parent.width
            radius: 5
            color: "transparent"
            border.color: myPlayer.repeat? "#2E4D5F" : "transparent"
        }
    }

    Image{
        id: idShuffleBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: idRepeatBtn.left
        anchors.rightMargin: idcontrolArea.height/2
        width: 2*idcontrolArea.height/3
        height: width
        source: Pic.shuffle
        MouseArea {
            id: idShuffle
            anchors.fill: parent
            onClicked: {
//                myControl.changeMute()
            }
        }
        Rectangle{
            implicitHeight: parent.height
            implicitWidth: parent.width
            color: "transparent"
//            border.color: repeat? "#2E4D5F" : "transparent"
        }
    }

    Rectangle{
        id: idcontrolArea
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: idControlBtn.width * 4
        height: parent.height/3
        radius: height/3*2
        border.color: "#2E4D5F"
        color: "white"

        //play/pause button
        Image{
            id: idControlBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            enabled: (idListView.count === 0)? false : true;
            width: parent.height
            height: width
            property bool playing: (myPlayer.state === 1)
            source: playing? Pic.pause : Pic.play
            MouseArea {
                id: idPlayPause
                anchors.fill: parent
                onClicked: {
                    myControl.playpause()
                }

            }

            Rectangle{
                anchors.centerIn: parent
                width: parent.width * 1.3
                height: width
                radius: width/2
                z: -1
                border.color: "#2E4D5F"
                color: "white"
            }
        }

        //next button
        Image{
            id: idNextBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: idControlBtn.right
            anchors.margins: idControlBtn.height/2
            enabled: (idListView.count === 0)? false : true;
            width: 2*parent.height/3
            height: width
            source: Pic.next
            MouseArea {
                id: idNext
                anchors.fill: parent
                onClicked: {
                    myControl.nextSong()
                }
            }
        }

        //previous button
        Image{
            id: idPreviousBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: idControlBtn.left
            anchors.margins: idControlBtn.height/2
            enabled: (idListView.count === 0)? false : true;
            width: 2*parent.height/3
            height: width
            source: Pic.previous
            MouseArea {
                id: idPrevious
                anchors.fill: parent
                onClicked: {
                    if (idListView.currentIndex > 0)
                    {
                        myControl.previousSong()
                    }
                }
            }
        }
    }
}
