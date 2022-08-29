import QtQuick 2.0
import "../libs/Lib.js" as RS
import "./buttons"

Repeater {
    id: idRpt
    property int currentIndex
    property var listMode : [qsTr("Playlist"), qsTr("Artist"), qsTr("Album"), qsTr("Mylist")]
    model: RS.listMode.length
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("main window created")
    }
    Column
    {
        QRectButton {
            color: "#151A7B"
            text: listMode[index]
            onBtnClicked:
            {
                myControl.setMode(index)
                console.log("currentMode: ", myData.currentMode)
            }
        }
        Rectangle {
            color: (myData.currentMode === index)? "#151A7B" : "transparent"
            height: 5
            width: 80
            radius: 3
        }
    }
}
