import QtQuick 2.0
import "../libs/Lib.js" as RS
import "../general"
import "../general/buttons"

Column {
    id: idSongList
    spacing: 6
    Component.onCompleted:
    {
        myControl.retranslate()
    }
    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        QTabBar
        {
            id: idTabBar
        }
    }
    Loader {
        id: listLoader
        width: idListView.width
        height: parent.height
        source: RS.listMode[myData.currentMode].comsrc;
    }
}
