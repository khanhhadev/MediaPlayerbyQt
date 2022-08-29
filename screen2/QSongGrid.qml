import QtQuick
import "../libs/Lib.js" as RS

import "../general"
import "../general/delegates"

QBasicList{
    id: idSongGrid
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("songGrid created")
    }
    delegate: QSong2 {
        width: idSongGrid.width - 20
        height: 50
    }

    spacing: 3
    height: parent.height
    model: myData
    currentIndex: myControl.currentIndex
}
