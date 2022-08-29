import QtQuick
import "../libs/Lib.js" as RS
import "../general"
import "../general/buttons"
import "../general/delegates"

QBasicList{
    id: idSongList
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("songList created")
    }
    delegate: QSong
    {
        width: idSongList.width

        QImgButton{
            id: heart
            width: 20
            height: 20
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            source: love? RS.Pic.hearted : RS.Pic.heart
            onBtnClicked: myControl.addFavourite(index)
        }
    }
    spacing: 3
    height: parent.height
    model: myData
    currentIndex: myControl.currentIndex
}
