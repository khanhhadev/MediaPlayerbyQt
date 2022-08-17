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
    objectName: "MainObject"

    //back ground
    Image {
        id: idBackground
        anchors.fill: parent
        source: Pic.background
        z: -1
    }

    MusicalArea {
        id: idMusicalArea
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 15
    }

    LanguageBox {
        anchors.top: idMusicalArea.top
        anchors.right: idMusicalArea.right
        anchors.margins: 5
    }

    //containing playlist
    SongList{
        id: idListView
        anchors.left: idMusicalArea.right
        anchors.leftMargin: 23
        anchors.right: parent.right
        anchors.rightMargin: 23
        anchors.top: parent.top
        anchors.topMargin: 23
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        width: 170;
        spacing: 3
        currentIndex: myControl.currentIndex
        model: myData
    }

    //containing media control buttons
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
