import QtQuick 2.0
import "../libs/Lib.js" as RS
import "../general"
import "../general/delegates"

QBasicList{
    id: idAlbumList
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("albumList created")
    }
    delegate: QSong
    {
        text: " " + album
        width: idAlbumList.width

        onClicked: {
            myData.currentAlbum = index
            myControl.selectSong(0, false);
        }
        onDoubleClicked: {
            myData.currentAlbum = index
            myControl.selectSong(0, true);
        }
    }
    spacing: 3
    height: parent.height
    model: myData
    currentIndex: myData.currentAlbum
}
