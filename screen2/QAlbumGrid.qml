import QtQuick 2.0
import "../libs/Lib.js" as RS

import "../general"
import "../general/delegates"
import CustomImage 1.0

//QBasicList{
GridView{
    id: idAlbumGrid
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("albumGrid created")
    }

    delegate: QAlbum {
        //        width: idAlbumGrid.width
        onClicked: {
            myData.currentAlbum = index
            myControl.selectSong(0, false);
        }
        onDoubleClicked: {
            myData.currentAlbum = index
            myControl.selectSong(0, true);
        }
    }
    cellHeight: 140
    cellWidth: 120
    height: parent.height
    model: myData
    currentIndex: myData.currentAlbum
}
