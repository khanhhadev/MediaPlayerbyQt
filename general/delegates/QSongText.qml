import QtQuick 2.0

Text {
    id: idText
    text: " " + name
    + '\n' + " Album: " + album
    + '\n' + " Artist: " + artist
    fontSizeMode: Text.Fit
    color: parent.focus? Color.songtext1 : Color.songtext2
    elide: Text.ElideRight
    verticalAlignment: Text.AlignVCenter
}
