import QtQuick
import "../libs/ImageLib.js" as Pic
import "../libs/ColorLib.js" as Color
import "./subcomponents"

ListView {
    Component {
        id: fileDelegate
        Rectangle{
            id: idRect
            height: 35
            implicitWidth: idListView.width
            radius: 3
            opacity: 1
            clip: true
            color: focus? Color.songback1 : Color.songback2
            border.color: focus? Color.songborder1 : Color.songborder2
            states: [State{
                    when: idRect.focus

                    PropertyChanges {
                        target: idRect
                        border.color: "white"
                        height: 90
                    }

                    PropertyChanges {
                        target: idText
                        verticalAlignment: Text.AlignTop
                    }

                    PropertyChanges {
                        target: idSongInfo
                        text: '\n' + "Tittle: " + myPlayer.currentSong[1]
                        + '\n' + "Album: " + myPlayer.currentSong[2]
                        + '\n' + "Artist: " + myPlayer.currentSong[3]
                        + '\n'+ myPlayer.currentSong[4]
                    }
                }, State{
                    when: playArea.containsMouse
                    PropertyChanges {
                        target: idRect
                        scale: 1.1
                    }
                }

            ]

            Text {
                id: idText
                text: " " + name
                fontSizeMode: Text.Fit
                color: parent.focus? Color.songtext1 : Color.songtext2
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: idSongInfo
                text: ""
                fontSizeMode: Text.Fit
                color: parent.focus? Color.songtext1 : Color.songtext2
                elide: Text.ElideRight
            }

            onFocusChanged: {
                if (!focus) idText.x = parent.x
                console.log(myPlayer.currentSong)
            }

            //text moving animation
            NumberAnimation{
                properties: "x"
                target: idText
                from: idRect.x
                to: idRect.x - idRect.width
                duration: 4000
                loops: Animation.Infinite
                running: idRect.focus? true: false
            }

            MouseArea {
                id: playArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    myControl.selectSong(index);
                }
                onDoubleClicked: {
                    myControl.selectSong(index);
                    myControl.playpause()
                }
            }
        }
    }

    delegate: fileDelegate

    Rectangle{
        id: listBackGround
        anchors{
            fill: parent
            left: parent.left
            leftMargin: -7
            right: parent.right
            rightMargin: -7
            top: parent.top
            topMargin: -7
            bottom: parent.bottom
            bottomMargin: -70
        }
        clip: true
        radius: 5
        opacity: 0.6
        z: -1
        implicitHeight: parent.height
        color: "white"
        border.color: "white"
    }

    Image
    {
        id: openFolder
        anchors{
            bottom: listBackGround.bottom
            right: parent.right
        }
        width: parent.width/7
        height: width
        source: Pic.folder

        MouseArea{
            id: openFolderArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                myControl.changeDirectory();
            }
        }
        HoverHandler {
            id: stylus
            acceptedDevices: PointerDevice.Stylus
            cursorShape: Qt.CrossCursor
        }
        MouseLabel{
            mouseID: openFolderArea
            mouseLabel: qsTr("Open Folder...")
            imgID: openFolder
        }
    }

    Image
    {
        id: addSong
        anchors{
            bottom: listBackGround.bottom
            right: openFolder.left
            rightMargin: 10
        }
        width: parent.width/7
        height: width
        source: Pic.add

        MouseArea{
            id: addSongArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                myControl.addFiles();
            }
        }

        MouseLabel{
            mouseID: addSongArea
            mouseLabel: qsTr("Add Songs...")
            imgID: addSong
        }
    }

    Image
    {
        id: sortList
        anchors{
            bottom: listBackGround.bottom
            right: addSong.left
            rightMargin: 10
        }
        width: parent.width/7
        height: width
        source: Pic.sort

        MouseArea{
            id: sortListArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                myControl.sortList();
            }
        }

        MouseLabel{
            mouseID: sortListArea
            mouseLabel: qsTr("Sort by name")
            imgID: sortList
        }
    }
}

