import QtQuick 2.15
import "../libs/ImageLib.js" as Pic
import "../libs/ColorLib.js" as Color
import "./subcomponents"
Item {

    //current playing time
    Text{
        id: songPosition
        anchors {
            verticalCenter: idProgressBar.verticalCenter
            left: parent.left
        }
        text: myPlayer.positionText
    }

    //total time of song
    Text{
        id: songDuration
        anchors{
            verticalCenter: idProgressBar.verticalCenter
            right: parent.right
        }
        text: myPlayer.durationText
    }

    //song progress display
    MSlider{
        id: idProgressBar
        anchors{
            top: parent.top
            left: songPosition.right
            right: songDuration.left
            margins: 10
        }
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
        anchors{
            right: songDuration.right
            margins: 3
            verticalCenter: parent.verticalCenter
        }
        radius: 3
        width: parent.width/4
        height: 10
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
        anchors{
            verticalCenter: parent.verticalCenter
            right: idVolumeBar.left
            rightMargin: width/4
        }
        width: idcontrolArea.height*2/3
        height: width
        property bool mute: (myPlayer.volume === 0)||(myPlayer.muted)
        source: mute? Pic.mute : Pic.volume

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

    Image{
        id: idRepeatBtn
        anchors{
            verticalCenter: parent.verticalCenter
            right: idcontrolArea.left
            rightMargin: idcontrolArea.height
        }
        width: idcontrolArea.height
        height: width*2/3
        source: Pic.repeat
        MouseArea {
            id: idRepeat
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                myControl.changeRepeat()
            }
        }

        MouseLabel{
            mouseID: idRepeat
            mouseLabel: qsTr("Repeat")
            imgID: idRepeatBtn
        }

        Rectangle{
            implicitHeight: parent.height
            implicitWidth: parent.width
            radius: 5
            z: -1
            color: myPlayer.repeat? Color.buttonback1 : Color.buttonback2
        }
    }

    Image{
        id: idShuffleBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: idRepeatBtn.left
        anchors.rightMargin: idcontrolArea.height
        width: idcontrolArea.height
        height: width*2/3
        source: Pic.shuffle
        MouseArea {
            id: idShuffle
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                myControl.changeShuffle()
            }
        }

        MouseLabel{
            mouseID: idShuffle
            mouseLabel: qsTr("Shuffle")
            imgID: idShuffleBtn
        }


        Rectangle{
            implicitHeight: parent.height
            implicitWidth: parent.width
            radius: 5
            z: -1
            color: myControl.shuffle? Color.buttonback1 : Color.buttonback2
        }
    }

    Rectangle{
        id: idcontrolArea
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: idControlBtn.width * 4
        height: parent.height/4
        radius: height/3*2
        border.color: Color.border
        color: "white"

        //play/pause button
        Image{
            property bool playing: (myPlayer.state === 1)
            id: idControlBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            enabled: (idListView.count === 0)? false : true;
            width: parent.height
            height: width
            source: playing? Pic.pause : Pic.play

            MouseArea {
                id: idPlayPause
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    myControl.playpause()
                }

            }

            MouseLabel{
                mouseID: idPlayPause
                mouseLabel: parent.playing? qsTr("Pause") : qsTr("Play")
                rectID: center
                imgID: idControlBtn
            }

            Rectangle{
                id: center
                anchors.centerIn: parent
                width: parent.width * 1.2
                height: width
                radius: width/2
                z: -1
                color: Color.buttonback1
                border.color: Color.border
            }
        }

        //next button
        Image{
            id: idNextBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: idControlBtn.right
            anchors.margins: idControlBtn.height/3
            enabled: (idListView.count === 0)? false : true;
            width: parent.height
            height: width*2/3
            source: Pic.next

            MouseArea {
                id: idNext
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    myControl.nextSong()
                }
            }

            MouseLabel{
                mouseID: idNext
                mouseLabel: qsTr("Next")
                imgID:  idNextBtn
            }
        }

        //previous button
        Image{
            id: idPreviousBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: idControlBtn.left
            anchors.margins: idControlBtn.height/3
            enabled: (idListView.count === 0)? false : true;
            width: parent.height
            height: width*2/3
            source: Pic.previous
            MouseArea {
                id: idPrevious
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if (idListView.currentIndex > 0)
                    {
                        myControl.previousSong()
                    }
                }
            }

            MouseLabel{
                mouseID: idPrevious
                mouseLabel: qsTr("Previous")
                imgID:  idPreviousBtn
            }
        }
    }
}
