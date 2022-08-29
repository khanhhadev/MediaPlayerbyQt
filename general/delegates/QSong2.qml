import QtQuick 2.0
import CustomImage 1.0
import "../../libs/Lib.js" as RS
import "../../general"
import "../../general/buttons"


QTextBox{
    id: idSong
    hoverEnabled: false
    width: parent.width - 20
    color: focus? RS.Color.songback1 : RS.Color.songback2
    border.color: focus? RS.Color.songborder1 : RS.Color.songborder2
    onClicked: {
        myControl.selectSong(index, false);
    }
    onDoubleClicked: {
        myControl.selectSong(index, true);
    }
    Row{
        width: parent.width
        spacing: 20

       ImageItem{
            id: idMusicPlay
            width: songName.height
            height: width
            anchors.verticalCenter: parent.verticalCenter
            image: eimage
        }

        Rectangle{
            id: songName
            height: 50
            width: /*(idSong.width - heart.width - idMusicPlay.width)/3*/ idSong.width/4
            border.width: 1
            color: "transparent"

            Text {
//                id: idTextBox
                text: " " + name
                fontSizeMode: Text.Fit
                color: idSong.focus? RS.Color.songtext1 : RS.Color.songtext2
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        Rectangle{
            id: songArtist
            height: 50
            width: /*(idSong.width - heart.width - idMusicPlay.width)/3*/ idSong.width/4
            border.width: 1
            color: "transparent"
            Text {
                text: " " + artist
                fontSizeMode: Text.Fit
                color: idSong.focus? RS.Color.songtext1 : RS.Color.songtext2
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
        Rectangle{
            id: songAlbum
            height: 50
            width: /*(idSong.width - heart.width - idMusicPlay.width)/3*/ idSong.width/4
            border.width: 1
            color: "transparent"

            Text {
                text: " " + album
                fontSizeMode: Text.Fit
                color: idSong.focus? RS.Color.songtext1 : RS.Color.songtext2
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }

        QImgButton{
            id: heart
            width: 20
            height: 20
            source: love? RS.Pic.hearted : RS.Pic.heart
            onBtnClicked: myControl.addFavourite(index)
        }
    }
}
