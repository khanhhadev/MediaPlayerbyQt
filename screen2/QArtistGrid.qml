import QtQuick 2.0
import "../libs/Lib.js" as RS

import "../general"
import "../general/delegates"

//QBasicList{
GridView{
    id: idArtistGrid
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("artistGrid created")
    }
    delegate: QArtist {
        //        width: idAlbumGrid.width
        onClicked: {
            myData.currentArtist = index
            myControl.selectSong(0, false);
        }
        onDoubleClicked: {
            myData.currentArtist = index
            myControl.selectSong(0, true);
        }
    }
    cellHeight: 140
    cellWidth: 120
    height: parent.height
    model: myData
    currentIndex: myData.currentArtist
}
