import QtQuick 2.15
import "../libs/Lib.js" as RS
import "./buttons"

Rectangle {
    id: idPlayArea
    height: 150
    color: "#151A7B"
    Row{
        id: idProgressDP
        spacing: (parent.width - (songDuration.width + songPosition.width + idProgressBar.width))/3
        anchors.horizontalCenter: parent.horizontalCenter

        //current playing time
        Text{
            id: songPosition
            text: myPlayer.positionText
            color: "white"
        }

        //song progress display
        QSlider{
            id: idProgressBar
            radius: 3
            width: idPlayArea.width*5/6
            height: 12
            maxValue: myPlayer.duration
            currentValue: myPlayer.position
            onMcurrentValueChanged: (value)=> {
                                        myPlayer.position = value
                                    }
        }

        //total time of song
        Text{
            id: songDuration
            color: "white"
            text: myPlayer.durationText
        }

    }

    //volume display
    QSlider{
        id: idVolumeBar
        anchors{
            right: idProgressDP.right
            margins: 3
            verticalCenter: parent.verticalCenter
        }
        radius: 3
        width: 180
        height: 10
        maxValue: 1
        currentValue: myPlayer.volume
        onMcurrentValueChanged: (value)=> {
                                    myPlayer.volume = value
                                }
    }

    //mute/unmute button
    QImgButton {
        id: idMuteBtn
        property bool mute: (myPlayer.volume === 0)||(myPlayer.muted)
        anchors{
            verticalCenter: parent.verticalCenter
            right: idVolumeBar.left
            rightMargin: width/4
        }
        source: mute? RS.Pic.mute : RS.Pic.volume
        btnLabel: mute? qsTr("Unmute") : qsTr("Mute")
        onBtnClicked: {
            myControl.changeMute()
        }
    }

    Row{
        spacing: 25
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }

        QImgButton{
            id: idShuffleBtn
            source: RS.Pic.shuffle
            btnLabel: qsTr("Shuffle")
            onBtnClicked: myControl.changeShuffle()
            border: myControl.shuffle? "white" : "transparent"
        }

        //previous button
        QImgButton{
            id: idPreviousBtn
            source: RS.Pic.previous
            btnLabel: qsTr("Previous")
            onBtnClicked: myControl.previousSong()
        }

        //play/pause button
        QImgButton{
            property bool playing: (myPlayer.state === 1)
            id: idPlayBtn
            width: 55
            source: playing? RS.Pic.pause : RS.Pic.play
            btnLabel: parent.playing? qsTr("Pause") : qsTr("Play")
            onBtnClicked:myControl.playpause()
        }

        //next button
        QImgButton{
            id: idNextBtn
            source: RS.Pic.next
            btnLabel: qsTr("Next")
            onBtnClicked: myControl.nextSong()
        }

        QImgButton{
            id: idRepeatBtn
            source: RS.Pic.repeat
            btnLabel: qsTr("Repeat")
            onBtnClicked: myControl.changeRepeat()
            border: myPlayer.repeat? "white" : "transparent"
        }
    }
}
