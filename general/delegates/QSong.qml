import QtQuick 2.0
import "../../libs/Lib.js" as RS
import "../buttons"

QTextBox
{
    text: " " + name
          + '\n' + qsTr(" Album: ") + album
          + '\n' + qsTr(" Artist: ") + artist
    onClicked: {
        myControl.selectSong(index, false);
    }
    onDoubleClicked: {
        myControl.selectSong(index, true);
    }
}

