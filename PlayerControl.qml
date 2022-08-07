import QtQuick 2.0
import QtMultimedia

Item {
    Rectangle {
        id: idProgressBar
        anchors.top: parent.top
        anchors.topMargin: 10
        implicitWidth: parent.width
        radius: 3
        height: 12
        color: "white"

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: idProgressPoint
            drag.axis: Drag.XAxis
            //            onReleased: parent = tile.Drag.target !== null ? tile.Drag.target : root
            //! [0]
            Rectangle {
                id: idProgressPoint
                x: (parent.width - width)*myPlayer.position/myPlayer.duration
                width: 20
                height: 12
                radius: 3
                color: "#2E4D5F"
                Drag.active: mouseArea.drag.active
                onXChanged: {
                    myPlayer.position = myPlayer.position + mouseArea.drag.x - idProgressBar.x
                }

                states: [State {
                        when: mouseArea.drag.active
                        PropertyChanges{
                            target: idProgressPoint
                            x: undefined
                        }
                    } ,
                    State {
                        when: !mouseArea.drag.active
                        PropertyChanges{
                            target: idProgressPoint
                            x: (parent.width - width)*myPlayer.position/myPlayer.duration
                        }
                    }
                ]
            }
        }




        Rectangle {
            id: idProgressRange
            width: idProgressPoint.x - x + idProgressPoint.width/2
            height: 12
            radius: 3
            color: "#877194"
        }
        //        DropArea{
        //            id: dragTarget
        //            width: parent.width
        //            height: parent.height
        //            Rectangle {
        //                id: idProgressPoint
        //                x: (parent.width - width)*myPlayer.position/myPlayer.duration
        //                width: 20
        //                height: 12
        //                radius: 3
        //                color: "#2E4D5F"
        //                onXChanged: {
        //                    console.log("drg")
        //                }

        //                //                states: State {
        //                //                    when: idDrag.drag.active
        //                //                    PropertyChanges{
        //                //                        target: idProgressPoint
        //                //                        x: dragTarget.drag.x
        //                //                    }
        //                //                }

        //                //                MouseArea {
        //                //                    id: idDrag
        //                //                    drag.target: parent
        //                //                    drag.maximumX : idProgressBar.width - idProgressPoint.width + idProgressBar.x
        //                //                    drag.minimumX : idProgressBar.x
        //                //                    drag.axis: Drag.XAxis
        //                //                    drag.active: true
        //                //                }
        //            }
        //        }
    }

    Image{
        id: idControlBtn
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: (idListView.count === 0)? false:true;
        opacity: (idListView.count === 0)? 0.5 : 1;
        width: 60
        height: 60
        source: (myPlayer.state === 1)?"qrc:/image/pause.png" : "qrc:/image/play.png"
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
        width: 60
        height: 60
        source: "qrc:/image/next.png"
        MouseArea {
            id: idNext
            anchors.fill: parent
            onClicked: {
                if (idListView.currentIndex < idListView.count - 1)
                {
                    var temp = myPlayer.state
                    idListView.currentIndex = idListView.currentIndex +1
                    myPlayer.state = temp
                } else
                {
                    myPlayer.position = myPlayer.duration
                    myPlayer.stop()
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
        width: 60
        height: 60
        source: "qrc:/image/previous.png"
        MouseArea {
            id: idPrevious
            anchors.fill: parent
            onClicked: {
                if (idListView.currentIndex > 0)
                {
                    var temp = myPlayer.state
                    idListView.currentIndex = idListView.currentIndex - 1
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
