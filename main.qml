import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Dialogs
import QtQuick.Layouts
import Qt.labs.platform
import "ImageLib.js" as Pic


Window {
    id: mainWindow
    signal qmlChangeDirectory(msg: string)

    width: 900
    height: 640
    visible: true
    title: qsTr("Media Player")
    objectName: "MainObject"

//    Component{
//        id: idcom
//        property int v
//        Rectangle{
//            width: 100
//            height: 100
//        }
//    }
//    Loader{
//        sourceComponent: idcom
//    }

    Image {
        id: idBackground
        anchors.fill: parent
        source: Pic.background
        z: -1
    }

    MusicalArea{
        id: idMusicalArea
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 15
    }

    SongList{
        id: idListView
        anchors.left: idMusicalArea.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 23
        width: 170;
        spacing: 3
        currentIndex: myData.currentIndex
        model: myData.songList
    }

    PlayerControl{
        id: idMediaControl
        anchors.fill: parent.horizontal
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: idMusicalArea.bottom
        anchors.right: idListView.left
        anchors.rightMargin: 23
        anchors.bottom: parent.bottom
        height: parent.height - idMusicalArea.height
        width: parent.width

    }
}
