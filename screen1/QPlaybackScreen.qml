import QtQuick 2.15
import QtQuick.Window 2.12
import "../libs/Lib.js" as RS
import "../general"

Row {
    visible: true
    spacing: 20
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("screen1 created")
    }
    QMusicalArea {
        id: idMusicalArea
        height: parent.height
        width: parent.width - idListView.width
    }

    QTabBar1 {
        id: idListView
        height: parent.height
        width: 300
    }
}
