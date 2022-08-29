import QtQuick 2.0
import "../libs/Lib.js" as RS
import "../general"
import "../general/buttons"

Row {
    id: idSongList
    spacing: 6
    Component.onCompleted:
    {
        myControl.retranslate()
    }
    Column {
        QTabBar
        {
            id: idTabBar
        }
    }
    Loader {
        id: listLoader
        width: parent.width
        height: parent.height
        source: RS.listMode[myData.currentMode].comsrc2;
    }
}
