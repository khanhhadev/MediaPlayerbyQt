import QtQuick 2.0
import QtMultimedia
import "ImageLib.js" as Pic

Item {
    Rectangle {
        id: idProgressBar
        anchors.top: parent.top
        anchors.topMargin: 10
        implicitWidth: parent.width
        radius: 3
        height: 12
        clip: true
        color: "white"

        Rectangle {
            id: idProgressRange
            width: idProgressPoint.x - x + idProgressPoint.width / 2
            height: 12
            radius: 3
            color: "#877194"
        }

        MouseArea {
            id: progressArea
            anchors.fill: parent
            onClicked: (event) => {
                           myPlayer.position = myPlayer.duration * (event.x)/(idProgressBar.width - idProgressPoint.width)
                       }

            Rectangle {
                id: idProgressPoint
                x: (idProgressBar.width - width) * myPlayer.position / myPlayer.duration
                width: idProgressBar.width/20
                height: 12
                z: 1
                radius: 3
                color: "#2E4D5F"
                Drag.active: progressDrag.drag.active
                onXChanged: {
                    if (progressDrag.drag.active) myPlayer.position = myPlayer.duration * x/(idProgressBar.width - width)
                }

                states: [State {
                    when: progressDrag.drag.active
                    PropertyChanges{
                        target: idProgressPoint
                        color: "#253E4C"
                        x: progressDrag.x
                    }
                },
                State {
                    when: progressArea.released
                    PropertyChanges{
                        target: idProgressPoint
                        color: "#253E4C"
                        x: progressArea.x
                    }
                }
            ]

                MouseArea {
                    id: progressDrag
                    anchors.fill: parent
                    drag.target: idProgressPoint
                    drag.axis: Drag.XAxis
                    drag.minimumX: 0
                    drag.maximumX: idProgressBar.width - idProgressPoint.width
                }
            }
        }
    }


    Rectangle {
        id: idVolumeBar
        anchors.left: idMuteBtn.right
        anchors.right: parent.right
        anchors.margins: 5
        anchors.verticalCenter: parent.verticalCenter
        radius: 3
        height: 7
        color: "white"
        clip: true

        Rectangle {
            id: idVolumeRange
            width: idVolumePoint.x - x + idVolumePoint.width / 2
            height: 7
            radius: 3
            color: "#877194"
        }

        MouseArea {
            id: volumeArea
            anchors.fill: parent
            onClicked: (event) => {
                           myPlayer.volume = (event.x)/ (idVolumeBar.width - idVolumePoint.width)
                       }

            Rectangle {
                id: idVolumePoint
                x:(idVolumeBar.width - width) * myPlayer.volume
                width: idVolumeBar.width / 15
                height: 12
                z: 1
                radius: 3
                color: "#2E4D5F"
                Drag.active: volumeDrag.drag.active
                onXChanged: {
                    if (volumeDrag.drag.active) myPlayer.volume = x / (idVolumeBar.width - width)
                }

                states: [State {
                        when: volumeDrag.drag.active
                        PropertyChanges{
                            target: idVolumePoint
                            color: "#253E4C"
                            x: volumeDrag.x
                        }
                    },
                    State {
                        when: volumeArea.released
                        PropertyChanges{
                            target: idVolumePoint
                            color: "#253E4C"
                            x: volumeArea.x
                        }
                    }
                ]

                MouseArea {
                    id: volumeDrag
                    anchors.fill: parent
                    drag.target: idVolumePoint
                    drag.axis: Drag.XAxis
                    drag.minimumX : 0
                    drag.maximumX: idVolumeBar.width - idVolumePoint.width
                }
            }
        }
    }

    Image{
        id: idControlBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: (idListView.count === 0)? false:true;
        opacity: (idListView.count === 0)? 0.5 : 1;
        width: parent.height/4
        height: width
        source: (myPlayer.state === 1)? Pic.pause : Pic.play
        MouseArea {
            id: idPlayPause
            anchors.fill: parent
            onClicked: {
                if (myPlayer.isPlaying()) myPlayer.pause()
                else myPlayer.play()
                console.log((myPlayer.state === 1));
            }
        }
    }

    Image{
        id: idNextBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: idControlBtn.right
        anchors.margins: 30
        opacity: (idListView.count === 0)? 0.5 : 1;
        width: parent.height/4
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

    Image{
        id: idPreviousBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: idControlBtn.left
        anchors.margins: 30
        opacity: (idListView.count === 0)? 0.5 : 1;
        width: parent.height/4
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

    Image{
        id: idMuteBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: idNextBtn.right
        anchors.leftMargin: idNextBtn.width
        anchors.right: parent.right
        anchors.rightMargin: 2*idNextBtn.width
        height: width
        source: (myPlayer.volume === 0)? Pic.mute :Pic.volume
        MouseArea {
            id: idMute
            anchors.fill: parent
            onClicked: {
                if (parent.source == Pic.mute) myPlayer.unmute()
                else myPlayer.mute()
            }
        }

    }

}
