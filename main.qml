import QtQuick 2.15
import QtQuick.Window 2.12
import "./libs/ImageLib.js" as Pic
import "./subparts"
import "./subparts/subcomponents"

Window {
    id: mainWindow

    width: 900
    height: 640
    visible: true
    title: qsTr("Media Player")
    //    objectName: "MainObject"

    //back ground
    Image {
        id: idBackground
        anchors.fill: parent
        source: Pic.background
        z: -1
    }

    MusicalArea {
        id: idMusicalArea
        anchors{
            left: parent.left
            top: parent.top
            margins: 15
        }
    }

    LanguageBox {
        anchors{
            top: idMusicalArea.top
            right: idMusicalArea.right
            margins: 5
        }
    }

//    Row {
//        anchors{
//            left: idListView.left
//            bottom: idListView.top
//            bottomMargin: 7
//        }
//        Repeater{
//            model: 3
//            Rectangle{
//                height: 40
//                width: idListView.width/3
//                opacity: 0.7
//            }
//        }
//    }

    //containing playlist
    SongList{
        id: idListView
        anchors{
            left: idMusicalArea.right
            leftMargin: 23
            right: parent.right
            rightMargin: 23
            top: parent.top
            topMargin: 53
            bottom: parent.bottom
            bottomMargin: 100
        }
        width: 170;
        spacing: 3
        currentIndex: myControl.currentIndex
        model: myData
    }

    //containing media control buttons
    PlayerControl{
        id: idMediaControl
        anchors{
            fill: parent.horizontal
            left: parent.left
            leftMargin: 15
            top: idMusicalArea.bottom
            right: idListView.left
            rightMargin: 23
            bottom: parent.bottom
        }
        height: parent.height - idMusicalArea.height
        width: parent.width

    }
}
