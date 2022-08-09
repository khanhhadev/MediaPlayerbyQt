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
                if (parent.mute) myPlayer.unmute()
                else myPlayer.mute()
                parent.mute != parent.mute
            }
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
                    if (myPlayer.isPlaying()) myPlayer.pause()
                    else myPlayer.play()
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
                    if (idListView.currentIndex < idListView.count - 1)
                    {
                        var temp = myPlayer.state
                        myData.currentIndex++;
                        myPlayer.state = temp
                    } else
                    {
                        myPlayer.stop()
                        myPlayer.position = myPlayer.duration
                    }
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
                        var temp = myPlayer.state
                        myData.currentIndex--;
                        myPlayer.state = temp
                    } else
                    {
                        myPlayer.position = 0
                        myPlayer.stop()
                    }
                }
            }
        }
    }
}
