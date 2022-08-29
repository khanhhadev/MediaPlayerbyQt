import QtQuick 2.0
import "../libs/Lib.js" as RS
import "../general"
import "../general/delegates"

QBasicList{
    id: idArtistList
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("artistList created")
    }
    delegate: QSong
    {
        width: idArtistList.width
        text: " " + artist
        onClicked: {
            myData.currentArtist = index
            myControl.selectSong(0, false);
        }
        onDoubleClicked: {
            myData.currentArtist = index
            myControl.selectSong(0, true);
        }
    }
    spacing: 3
    height: parent.height
    model: myData
    currentIndex: myData.currentArtist
}
