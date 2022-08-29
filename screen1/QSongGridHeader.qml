import QtQuick 2.0
import "../general/delegates"
import "../libs/ColorLib.js" as Color

Item {
    Row{
        id: idSong

        Rectangle{
            width: songName.height
            height: width
            border.color: Color.songborder2
            border.width: 1
        }

        QTextBox
        {
            id: songName
            width: parent.width/4
            border.width: 1
            radius: 0
            text: "Song"
        }

        QTextBox{
            id: songArtist
            width: parent.width/4
            border.width: 1
            radius: 0
            text: "Artist"
        }

        QTextBox{
            id: songAlbum
            width: parent.width/4
            border.width: 1
            radius: 0
            text: "Album"
        }
    }
}
