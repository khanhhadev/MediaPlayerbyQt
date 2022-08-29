import QtQuick
import "../libs/Lib.js" as RS
import "./buttons"

ListView {
    width: 250

    Rectangle{
        id: listBackGround
        anchors{
            fill: parent
            left: parent.left
            leftMargin: -7
            right: parent.right
            rightMargin: -7
            top: parent.top
            topMargin: -7
            bottom: parent.bottom
            bottomMargin: -70
        }
        clip: true
        opacity: 0.6
        z: -1
        implicitHeight: parent.height
        color: "#151A7B"
        border.color: "white"
    }

//        QImgButton
//        {
//            id: sortList
//            width: 30
//            source: RS.sort
//            btnLabel: qsTr("Sort by name")
//            onBtnClicked: myControl.sortList()
//        }
//    }
}

