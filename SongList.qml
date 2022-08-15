import QtQuick 2.0
import "ImageLib.js" as Pic

ListView {
    signal qmlChangeDirectory()
    Component {
        id: fileDelegate
        Rectangle{
            id: idRect
            height: 35
            implicitWidth: idListView.width
            radius: 3
            border.color: focus? "white" : "#2E4D5F"
            opacity: 1
            clip: true
            color: focus? "#2E4D5F" : "transparent"
            states: State{
                when: idRect.focus
                PropertyChanges {
                    target: idRect
                    border.color: "white"
                    height: 90
                }
                PropertyChanges {
                    target: idText
                    //                    anchors.top: parent.top
                    verticalAlignment: Text.AlignTop
                }
                PropertyChanges {
                    target: idSongInfo
                    //                    anchors.top: idText.bottom
                    text: '\n' + "Tittle: " + myPlayer.currentSong[1]+ '\n' + "Album: " + myPlayer.currentSong[2] + '\n'
                    + "Artist: " + myPlayer.currentSong[3] + '\n'+ myPlayer.currentSong[4]
                }
            }
            Text {
                id: idText
                text: " " + name
                fontSizeMode: Text.Fit
                color: parent.focus? "white" : "black"
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                //                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                id: idSongInfo
                text: ""
                fontSizeMode: Text.Fit
                color: parent.focus? "white" : "black"
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
        anchors.fill: parent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: -7
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
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width/5
        height: width
        source: Pic.folder

        MouseArea{
            id: openFolderArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                qmlchangeDirectory();
            }
        }

        MouseLabel{
            mouseID: openFolderArea
            mouseLabel: qsTr("Open Folder...")
        }
    }

    Image
    {
        id: addSong
        anchors.bottom: parent.bottom
        anchors.right: openFolder.left
        anchors.rightMargin: 10
        width: parent.width/5
        height: width
        source: Pic.add

        MouseArea{
            id: addSongArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                qmladdFiles();
            }
        }

        MouseLabel{
            mouseID: addSongArea
            mouseLabel: qsTr("Add Songs...")
        }
    }

    Image
    {
        id: sortList
        anchors.bottom: parent.bottom
        anchors.right: addSong.left
        anchors.rightMargin: 10
        width: parent.width/5
        height: width
        source: Pic.sort

        MouseArea{
            id: sortListArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                qmlsortList();
            }
        }

        MouseLabel{
            mouseID: sortListArea
            mouseLabel: qsTr("Sort by name: ")
        }
    }
}

